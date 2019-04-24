#pragma once

#include "glpk.h"
#include "sdk_glpk_data.h"
#include <functional>

class GlpkCal:public glpk_pack::GlpkDatas
{
public:
	GlpkCal();
	virtual ~GlpkCal();
public:
	virtual bool Init();
	virtual void Uninit();
	virtual void SetTarget(std::vector<double>& tagetfun, glpk_pack::GLPK_TAGET tagetMinMax);
	
	bool HandleSubjects();
	bool HandleTargetParams();
	void GetSolutions(std::function<void(double*, int)> func);
protected:
	glp_prob *lp;
};