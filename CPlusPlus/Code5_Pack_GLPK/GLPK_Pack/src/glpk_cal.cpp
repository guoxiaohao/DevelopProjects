#include "pch.h"

#include "glpk_cal.h"

GlpkCal::GlpkCal()
{
}

GlpkCal::~GlpkCal()
{
}

bool GlpkCal::Init()
{
	glpk_pack::GlpkDatas::Init();
	
	lp = nullptr;
	lp = glp_create_prob();
	if(lp!=nullptr)
	{
		std::cout << glp_version() << std::endl;
		glp_set_prob_name(lp, "DatasHandle");
		
		m_bjson = m_resultjson.Init();
		
		return true;
	}
	else
	{
		return false;
	}
}

void GlpkCal::Uninit()
{
	m_resultjson.Uninit();
	glp_delete_prob(lp);
	glpk_pack::GlpkDatas::Uninit();
}

void GlpkCal::SetTarget(std::vector<double>& tagetfun, glpk_pack::GLPK_TAGET tagetMinMax)
{
	glpk_pack::GlpkDatas::SetTarget(tagetfun, tagetMinMax);
	
	if(m_MinMax==glpk_pack::GLPK_TAGET::TARGET_MIN)
	{
		glp_set_obj_dir(lp, GLP_MIN);
	}
	else
	{
		glp_set_obj_dir(lp, GLP_MAX);
	}
}

bool GlpkCal::HandleSubjects()
{
	bool bRets = true;
	
	if(m_vecSubCond.size()>0)
	{
		glp_add_rows(lp, m_vecSubCond.size());
	}
	
	char szBegin = 'a';
	for(size_t i=0; i< m_vecSubCond.size(); i++)
	{
		char szTmp[8] = {0};
		sprintf(szTmp, "%c", szBegin + i);
		glp_set_row_name(lp, i+1, szTmp);
		
		glpk_pack::SubjectInequal tmpSubject = m_vecSubCond[i];
		if(tmpSubject.params.size()!=m_tarfunpara.size())
		{
			bRets = false;
			break;
		}
		
		if(tmpSubject.tSide==glpk_pack::GLPK_SIDE::TARGET_DOWN)
		{
			glp_set_row_bnds(lp, i+1, GLP_DB, tmpSubject.lVal, tmpSubject.rVal);
		}
		else
		{
			glp_set_row_bnds(lp, i+1, GLP_LO, tmpSubject.lVal, tmpSubject.rVal);
		}
	}
	
	return bRets;
}

bool GlpkCal::HandleTargetParams()
{
	if(m_vecTargetParam.size()!=m_tarfunpara.size())
	{
		return false;
	}
	
	glp_add_cols(lp, m_vecTargetParam.size());
	for(size_t i=0; i<m_vecTargetParam.size(); i++)
	{
		char szTmp[8] = {0};
		sprintf(szTmp, "x%d", i+1);
		glp_set_col_name(lp, i+1, szTmp);
		
		if(m_vecTargetParam[i].tSide==glpk_pack::GLPK_SIDE::TARGET_DOWN)
		{
			glp_set_col_bnds(lp, i+1, GLP_DB, m_vecTargetParam[i].lVal, m_vecTargetParam[i].rVal);
		}
		else
		{
			glp_set_col_bnds(lp, i+1, GLP_LO, m_vecTargetParam[i].lVal, m_vecTargetParam[i].rVal);
		}
	}
        
	for(size_t i=0; i<m_tarfunpara.size(); i++)
	{
		glp_set_obj_coef(lp, i+1, m_tarfunpara[i]);
	}
	
	return true;
}

void GlpkCal::GetSolutions()
{
	int SumNum = m_vecSubCond.size() * m_vecTargetParam.size();
	
	int *ia = new int[SumNum+1];
	int *ja = new int[SumNum+1];
	double *ar = new double[SumNum+1];
	double *dRetValus = new double[m_vecTargetParam.size()+1];
	
	size_t i=0;
	for(size_t m=0; m<m_vecSubCond.size(); m++)
	{
		for(size_t n=0; n<m_vecSubCond[m].params.size(); n++)
		{
			i++;
			ia[i] = m+1;
			ja[i] = n+1;
			ar[i] = m_vecSubCond[m].params[n];
		}
	}
	glp_load_matrix(lp, SumNum, ia, ja, ar);
	glp_simplex(lp, NULL);
	
	dRetValus[0] = glp_get_obj_val(lp);
	std::cout << "Target Value "<< dRetValus[0] << std::endl;
	for(i=0; i<m_vecTargetParam.size(); i++)
	{
		dRetValus[i+1] = glp_get_col_prim(lp, i+1);
		std::cout << "Variable" << i+1 << " Value " << dRetValus[i+1] << std::endl;
	}
	m_resultjson.WriteDatas(dRetValus, m_vecTargetParam.size()+1);
	
	delete []ia;
	delete []ja;
	delete []ar;
	delete []dRetValus;
}