#include "pch.h"

#include "glpk_cal.h"
#include "result_json.h"

int main(int argc, char** argv)
{
	ResultJson resultJsons;
	bool bRets = resultJsons.Init();

/*
egs
Max
	z = 10x1 + 6x2 + 4x3;
Sub
	x1+x2+x3<=100
	10x1+4x2+5x3<=600
	2x1+2x2+6x3<=300
	x1>=0
	x2>=0
	x3>=0
*/

	std::vector<double> targetfunc;
	targetfunc.clear();
	glpk_pack::GLPK_TAGET tagets = glpk_pack::GLPK_TAGET::TARGET_MAX;
	targetfunc.push_back(10);
	targetfunc.push_back(6);
	targetfunc.push_back(4);

	glpk_pack::SubjectInequal condition1;condition1.params.clear();
	glpk_pack::SubjectInequal condition2;condition2.params.clear();
	glpk_pack::SubjectInequal condition3;condition3.params.clear();
	condition1.params.push_back(1);condition1.params.push_back(1);condition1.params.push_back(1);
	condition2.params.push_back(10);condition2.params.push_back(4);condition2.params.push_back(5);
	condition3.params.push_back(2);condition3.params.push_back(2);condition3.params.push_back(6);
	condition1.tSide = glpk_pack::GLPK_SIDE::TARGET_DOWN;
	condition2.tSide = glpk_pack::GLPK_SIDE::TARGET_DOWN;
	condition3.tSide = glpk_pack::GLPK_SIDE::TARGET_DOWN;
	condition1.lVal = 0.0;condition1.rVal = 100;
	condition2.lVal = 0.0;condition2.rVal = 600;
	condition3.lVal = 0.0;condition3.rVal = 300;

	glpk_pack::TargetParamRange targets1;
	glpk_pack::TargetParamRange targets2;
	glpk_pack::TargetParamRange targets3;
	targets1.lVal = 0;targets1.rVal = 0;
	targets2.lVal = 0;targets2.rVal = 0;
	targets3.lVal = 0;targets3.rVal = 0;
	targets1.tSide = glpk_pack::GLPK_SIDE::TARGET_UP;
	targets2.tSide = glpk_pack::GLPK_SIDE::TARGET_UP;
	targets3.tSide = glpk_pack::GLPK_SIDE::TARGET_UP;

	GlpkCal glpkcal;
	if(!glpkcal.Init())
	{
		std::cout << "Error: Init" << std::endl;
		return 1;
	}

	glpkcal.SetTarget(targetfunc, tagets);
	glpkcal.SetSubjectInequl(condition1);
	glpkcal.SetSubjectInequl(condition2);
	glpkcal.SetSubjectInequl(condition3);

	glpkcal.SetTargetParamRange(targets1);
	glpkcal.SetTargetParamRange(targets2);
	glpkcal.SetTargetParamRange(targets3);

	if(!glpkcal.HandleSubjects())
	{
		glpkcal.Uninit();
		std::cout << "Error: Suject Inequals" << std::endl;
		return 1;
	}
	if(!glpkcal.HandleTargetParams())
	{
		glpkcal.Uninit();
		std::cout << "Error: Target Params" << std::endl;
		return 1;
	}
	if(bRets)
	{
		glpkcal.GetSolutions(std::bind(&ResultJson::WriteDatas, &resultJsons, std::placeholders::_1, std::placeholders::_2));
	}
	else
	{
		glpkcal.GetSolutions(nullptr);
	}
	glpkcal.Uninit();

/*
eg1
Max
	z = 10x1 + 6x2;
Sub
	x1+x2<=200
	x1+2x2>=10
	3x1+x2<=275.5
	x1>=0
	x2>=0
*/

	targetfunc.clear();
	tagets = glpk_pack::GLPK_TAGET::TARGET_MAX;
	targetfunc.push_back(10);
	targetfunc.push_back(6);

	condition1.params.clear();
	condition2.params.clear();
	condition3.params.clear();
	condition1.params.push_back(1);condition1.params.push_back(1);
	condition2.params.push_back(1);condition2.params.push_back(2);
	condition3.params.push_back(3);condition3.params.push_back(1);
	condition1.tSide = glpk_pack::GLPK_SIDE::TARGET_DOWN;
	condition2.tSide = glpk_pack::GLPK_SIDE::TARGET_UP;
	condition3.tSide = glpk_pack::GLPK_SIDE::TARGET_DOWN;
	condition1.lVal = 0.0;condition1.rVal = 200;
	condition2.lVal = 10;condition2.rVal = 0.0;
	condition3.lVal = 0.0;condition3.rVal = 275.5;

	targets1.lVal = 0;targets1.rVal = 0;
	targets2.lVal = 0;targets2.rVal = 0;
	targets1.tSide = glpk_pack::GLPK_SIDE::TARGET_UP;
	targets2.tSide = glpk_pack::GLPK_SIDE::TARGET_UP;

	GlpkCal glpkcal1;
	if(!glpkcal1.Init())
	{
		std::cout << "Error: Init" << std::endl;
		return 1;
	}

	glpkcal1.SetTarget(targetfunc, tagets);
	glpkcal1.SetSubjectInequl(condition1);
	glpkcal1.SetSubjectInequl(condition2);
	glpkcal1.SetSubjectInequl(condition3);

	glpkcal1.SetTargetParamRange(targets1);
	glpkcal1.SetTargetParamRange(targets2);

	if(!glpkcal1.HandleSubjects())
	{
		glpkcal1.Uninit();
		std::cout << "Error: Suject Inequals" << std::endl;
		return 1;
	}
	if(!glpkcal1.HandleTargetParams())
	{
		glpkcal1.Uninit();
		std::cout << "Error: Target Params" << std::endl;
		return 1;
	}
	if(bRets)
	{
		glpkcal1.GetSolutions(std::bind(&ResultJson::WriteDatas, &resultJsons, std::placeholders::_1, std::placeholders::_2));
	}
	else
	{
		glpkcal1.GetSolutions(nullptr);
	}
	glpkcal1.Uninit();

	resultJsons.Uninit();

	return 0;
}