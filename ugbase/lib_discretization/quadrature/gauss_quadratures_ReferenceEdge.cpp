//This file is parsed from UG 3.9.


#include "quadrature.h"

namespace ug{

template <>
GaussQuadrature<ReferenceEdge>::GaussQuadrature(int order)
{
	switch(order)
	{
	case 1:
		m_order = 1;
		m_num_points = 1;

		if(allocate_memory(m_num_points) != true)
		{
			assert(0 && "Error while constructing Quadrature Rule.");
		}

		m_points[0][0] = 0.500000000000000000;

		m_weights[0] =  1.000000000000000000;
		break;

	case 3:
		m_order = 3;
		m_num_points = 2;

		if(allocate_memory(m_num_points) != true)
		{
			assert(0 && "Error while constructing Quadrature Rule.");
		}

		m_points[0][0] = 0.211324865405187118;
		m_points[1][0] = 0.788675134594812882;

		m_weights[0] =  0.500000000000000000;
		m_weights[1] =  0.500000000000000000;
		break;

	case 5:
		m_order = 5;
		m_num_points = 3;

		if(allocate_memory(m_num_points) != true)
		{
			assert(0 && "Error while constructing Quadrature Rule.");
		}

		m_points[0][0] = 0.112701665379258311;
		m_points[1][0] = 0.500000000000000000;
		m_points[2][0] = 0.887298334620741689;

		m_weights[0] =  0.277777777777777778;
		m_weights[1] =  0.444444444444444444;
		m_weights[2] =  0.277777777777777778;
		break;

	case 7:
		m_order = 7;
		m_num_points = 4;

		if(allocate_memory(m_num_points) != true)
		{
			assert(0 && "Error while constructing Quadrature Rule.");
		}

		m_points[0][0] = 0.069431844202973712;
		m_points[1][0] = 0.330009478207571868;
		m_points[2][0] = 0.669990521792428132;
		m_points[3][0] = 0.930568155797026288;

		m_weights[0] =  0.173927422568726929;
		m_weights[1] =  0.326072577431273071;
		m_weights[2] =  0.326072577431273071;
		m_weights[3] =  0.173927422568726929;
		break;

	case 9:
		m_order = 9;
		m_num_points = 5;

		if(allocate_memory(m_num_points) != true)
		{
			assert(0 && "Error while constructing Quadrature Rule.");
		}

		m_points[0][0] = 0.046910077030668004;
		m_points[1][0] = 0.230765344947158454;
		m_points[2][0] = 0.500000000000000000;
		m_points[3][0] = 0.769234655052841546;
		m_points[4][0] = 0.953089922969331996;

		m_weights[0] =  0.118463442528094544;
		m_weights[1] =  0.239314335249683234;
		m_weights[2] =  0.284444444444444444;
		m_weights[3] =  0.239314335249683234;
		m_weights[4] =  0.118463442528094544;
		break;

	case 11:
		m_order = 11;
		m_num_points = 6;

		if(allocate_memory(m_num_points) != true)
		{
			assert(0 && "Error while constructing Quadrature Rule.");
		}

		m_points[0][0] = 0.033765242898423986;
		m_points[1][0] = 0.169395306766867743;
		m_points[2][0] = 0.380690406958401546;
		m_points[3][0] = 0.619309593041598454;
		m_points[4][0] = 0.830604693233132257;
		m_points[5][0] = 0.966234757101576014;

		m_weights[0] =  0.085662246189585173;
		m_weights[1] =  0.180380786524069304;
		m_weights[2] =  0.233956967286345524;
		m_weights[3] =  0.233956967286345524;
		m_weights[4] =  0.180380786524069304;
		m_weights[5] =  0.085662246189585173;
		break;

	case 13:
		m_order = 13;
		m_num_points = 7;

		if(allocate_memory(m_num_points) != true)
		{
			assert(0 && "Error while constructing Quadrature Rule.");
		}

		m_points[0][0] = 0.025446043828620738;
		m_points[1][0] = 0.129234407200302780;
		m_points[2][0] = 0.297077424311301417;
		m_points[3][0] = 0.500000000000000000;
		m_points[4][0] = 0.702922575688698583;
		m_points[5][0] = 0.870765592799697220;
		m_points[6][0] = 0.974553956171379262;

		m_weights[0] =  0.064742483084434847;
		m_weights[1] =  0.139852695744638334;
		m_weights[2] =  0.190915025252559472;
		m_weights[3] =  0.208979591836734694;
		m_weights[4] =  0.190915025252559472;
		m_weights[5] =  0.139852695744638334;
		m_weights[6] =  0.064742483084434847;
		break;

	case 15:
		m_order = 15;
		m_num_points = 8;

		if(allocate_memory(m_num_points) != true)
		{
			assert(0 && "Error while constructing Quadrature Rule.");
		}

		m_points[0][0] = 0.019855071751231884;
		m_points[1][0] = 0.101666761293186630;
		m_points[2][0] = 0.237233795041835507;
		m_points[3][0] = 0.408282678752175098;
		m_points[4][0] = 0.591717321247824902;
		m_points[5][0] = 0.762766204958164493;
		m_points[6][0] = 0.898333238706813370;
		m_points[7][0] = 0.980144928248768116;

		m_weights[0] =  0.050614268145188130;
		m_weights[1] =  0.111190517226687235;
		m_weights[2] =  0.156853322938943644;
		m_weights[3] =  0.181341891689180991;
		m_weights[4] =  0.181341891689180991;
		m_weights[5] =  0.156853322938943644;
		m_weights[6] =  0.111190517226687235;
		m_weights[7] =  0.050614268145188130;
		break;

	case 17:
		m_order = 17;
		m_num_points = 9;

		if(allocate_memory(m_num_points) != true)
		{
			assert(0 && "Error while constructing Quadrature Rule.");
		}

		m_points[0][0] = 0.015919880246186955;
		m_points[1][0] = 0.081984446336682103;
		m_points[2][0] = 0.193314283649704801;
		m_points[3][0] = 0.337873288298095535;
		m_points[4][0] = 0.500000000000000000;
		m_points[5][0] = 0.662126711701904465;
		m_points[6][0] = 0.806685716350295199;
		m_points[7][0] = 0.918015553663317897;
		m_points[8][0] = 0.984080119753813045;

		m_weights[0] =  0.040637194180787206;
		m_weights[1] =  0.090324080347428702;
		m_weights[2] =  0.130305348201467731;
		m_weights[3] =  0.156173538520001420;
		m_weights[4] =  0.165119677500629882;
		m_weights[5] =  0.156173538520001420;
		m_weights[6] =  0.130305348201467731;
		m_weights[7] =  0.090324080347428702;
		m_weights[8] =  0.040637194180787206;
		break;

	case 19:
		m_order = 19;
		m_num_points = 10;

		if(allocate_memory(m_num_points) != true)
		{
			assert(0 && "Error while constructing Quadrature Rule.");
		}

		m_points[0][0] = 0.013046735741414140;
		m_points[1][0] = 0.067468316655507745;
		m_points[2][0] = 0.160295215850487797;
		m_points[3][0] = 0.283302302935376405;
		m_points[4][0] = 0.425562830509184395;
		m_points[5][0] = 0.574437169490815605;
		m_points[6][0] = 0.716697697064623595;
		m_points[7][0] = 0.839704784149512203;
		m_points[8][0] = 0.932531683344492255;
		m_points[9][0] = 0.986953264258585860;

		m_weights[0] =  0.033335672154344069;
		m_weights[1] =  0.074725674575290297;
		m_weights[2] =  0.109543181257991022;
		m_weights[3] =  0.134633359654998178;
		m_weights[4] =  0.147762112357376435;
		m_weights[5] =  0.147762112357376435;
		m_weights[6] =  0.134633359654998178;
		m_weights[7] =  0.109543181257991022;
		m_weights[8] =  0.074725674575290297;
		m_weights[9] =  0.033335672154344069;
		break;

	default: assert(0 && "Order not availabile. Can not construct GaussQuadrature.\n");
	}
}



template <>
bool RegisterQuadratureRule(QuadratureRuleProvider<ReferenceEdge>& factory)
{
	static GaussQuadrature<ReferenceEdge> gaussQuadratureReferenceEdge_1(1);
	static GaussQuadrature<ReferenceEdge> gaussQuadratureReferenceEdge_3(3);
	static GaussQuadrature<ReferenceEdge> gaussQuadratureReferenceEdge_5(5);
	static GaussQuadrature<ReferenceEdge> gaussQuadratureReferenceEdge_7(7);
	static GaussQuadrature<ReferenceEdge> gaussQuadratureReferenceEdge_9(9);
	static GaussQuadrature<ReferenceEdge> gaussQuadratureReferenceEdge_11(11);
	static GaussQuadrature<ReferenceEdge> gaussQuadratureReferenceEdge_13(13);
	static GaussQuadrature<ReferenceEdge> gaussQuadratureReferenceEdge_15(15);
	static GaussQuadrature<ReferenceEdge> gaussQuadratureReferenceEdge_17(17);
	static GaussQuadrature<ReferenceEdge> gaussQuadratureReferenceEdge_19(19);

	bool success = true;
	success &= factory.register_rule(gaussQuadratureReferenceEdge_1);
	success &= factory.register_rule(gaussQuadratureReferenceEdge_3);
	success &= factory.register_rule(gaussQuadratureReferenceEdge_5);
	success &= factory.register_rule(gaussQuadratureReferenceEdge_7);
	success &= factory.register_rule(gaussQuadratureReferenceEdge_9);
	success &= factory.register_rule(gaussQuadratureReferenceEdge_11);
	success &= factory.register_rule(gaussQuadratureReferenceEdge_13);
	success &= factory.register_rule(gaussQuadratureReferenceEdge_15);
	success &= factory.register_rule(gaussQuadratureReferenceEdge_17);
	success &= factory.register_rule(gaussQuadratureReferenceEdge_19);

	return true;
}


}; // namespace ug

/*
// register quadratures at factory
namespace {
using namespace ug;

template <>
std::vector<const QuadratureRule<ReferenceEdge>* > QuadratureRuleProvider<ReferenceEdge>::m_rules =
	std::vector<const QuadratureRule<ReferenceEdge>* >();
};
*/
