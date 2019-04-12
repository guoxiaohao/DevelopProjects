#include "sdk_glpk_data.h"



namespace glpk_pack{


GlpkDatas::GlpkDatas()
{

}

GlpkDatas::~GlpkDatas()
{

}

bool GlpkDatas::Init()
{
	m_tarfunpara.clear();
	m_vecSubCond.clear();
	m_vecTargetParam.clear();
	
	return true;
}

void GlpkDatas::Uninit()
{

}

void GlpkDatas::SetTarget(std::vector<double>& tagetfun, GLPK_TAGET tagetMinMax)
{
	for(size_t i = 0; i<tagetfun.size(); i++)
	{
		m_tarfunpara.push_back( tagetfun[i] );
	}
	m_MinMax = tagetMinMax;
}

void GlpkDatas::SetSubjectInequl(SubjectInequal& subjectinequal)
{
	m_vecSubCond.push_back(subjectinequal);
}

void GlpkDatas::SetTargetParamRange(TargetParamRange& tagetparam)
{
	m_vecTargetParam.push_back(tagetparam);
}


}