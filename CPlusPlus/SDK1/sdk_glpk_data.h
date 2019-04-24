#pragma once

#include <string>
#include <vector>

namespace glpk_pack{

enum GLPK_TAGET
{
	TARGET_MIN = 0,
	TARGET_MAX = 1
};

enum GLPK_SIDE
{
	TARGET_DOWN = 0,
	TARGET_UP = 1
};

struct SubjectInequal
{
	std::vector<double> params;
	double rVal;
	double lVal;
	GLPK_SIDE tSide;
};

struct TargetParamRange
{
	double rVal;
	double lVal;
	GLPK_SIDE tSide;
};

class GlpkDatas
{
public:
	GlpkDatas();
	virtual ~GlpkDatas();
public:
	virtual bool Init();
	virtual void Uninit();
	
	virtual void SetTarget(std::vector<double>& tagetfun, GLPK_TAGET tagetMinMax);
	virtual void SetSubjectInequl(SubjectInequal& subjectinequal);
	virtual void SetTargetParamRange(TargetParamRange& tagetparam);
protected:
	glpk_pack::GLPK_TAGET m_MinMax;
	std::vector<double> m_tarfunpara;
	std::vector<SubjectInequal> m_vecSubCond;
	std::vector<TargetParamRange> m_vecTargetParam;
};

}