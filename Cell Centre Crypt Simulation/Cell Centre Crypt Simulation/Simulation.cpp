
/****************************************************************************************

This file handles the highest level simulation functions, it creates all the items in the
simulation and updates them every frame.

****************************************************************************************/
namespace Simulation
{
	struct SimSetup
	{
		double averageGrowthTimeInSeconds;
		double membraneAttachmentForce;
		std::string filename;
		MutationData mutationData;
	};

	std::vector<Crypt*> crypts;
	std::string filename;
	SimSetup currentSettings;
	double mutationHeight = -100.0;
	NormalDistributionRNG* normalRNG;
	
	/*****************************************************************************

	The next set of functions create and populate a grid of crypts.  There is one
	function for each size of array, only call one of these, call it in the Init
	function, call the one that is the size of array you want.

	*****************************************************************************/
	void Setup1x1(double cellCycleTime, double attachmentForce)
	{
		Vector2D boundary(1500.0, 1500.0);
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(0.0f,0.0f,0.0f), 0));
	}

	void Setup5x5(double cellCycleTime, double attachmentForce)
	{
		Vector2D boundary(5500.0, 4000.0);
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,0.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,0.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,0.0f), 2));			
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,0.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,0.0f), 4));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(500.0f,0.0f,1500.0f), 5));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-1500.0f,0.0f,1500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-3500.0f,0.0f,1500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(2500.0f,0.0f,1500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(4500.0f,0.0f,1500.0f), 9));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,3000.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,3000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,3000.0f), 2));			
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,3000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,3000.0f), 4));
				
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(500.0f,0.0f,-1500.0f), 5));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-1500.0f,0.0f,-1500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-3500.0f,0.0f,-1500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(2500.0f,0.0f,-1500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(4500.0f,0.0f,-1500.0f), 9));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,-3000.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,-3000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,-3000.0f), 2));			
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,-3000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,-3000.0f), 4));
	}

	void Setup9x9(double cellCycleTime, double attachmentForce)
	{
		Vector2D boundary(15500.0, 11500.0);
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,0.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,0.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,0.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-6500.0f,0.0f,0.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-8500.0f,0.0f,0.0f), 2));			
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,0.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,0.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(5500.0f,0.0f,0.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(7500.0f,0.0f,0.0f), 4));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(500.0f,0.0f,1500.0f), 5));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-1500.0f,0.0f,1500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-3500.0f,0.0f,1500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-5500.0f,0.0f,1500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-7500.0f,0.0f,1500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(2500.0f,0.0f,1500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(4500.0f,0.0f,1500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(6500.0f,0.0f,1500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(8500.0f,0.0f,1500.0f), 9));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,3000.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,3000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,3000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-6500.0f,0.0f,3000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-8500.0f,0.0f,3000.0f), 2));			
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,3000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,3000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(5500.0f,0.0f,3000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(7500.0f,0.0f,3000.0f), 4));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(500.0f,0.0f,4500.0f), 5));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-1500.0f,0.0f,4500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-3500.0f,0.0f,4500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-5500.0f,0.0f,4500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-7500.0f,0.0f,4500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(2500.0f,0.0f,4500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(4500.0f,0.0f,4500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(6500.0f,0.0f,4500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(8500.0f,0.0f,4500.0f), 9));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,6000.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,6000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,6000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-6500.0f,0.0f,6000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-8500.0f,0.0f,6000.0f), 2));			
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,6000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,6000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(5500.0f,0.0f,6000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(7500.0f,0.0f,6000.0f), 4));
				
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(500.0f,0.0f,-1500.0f), 5));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-1500.0f,0.0f,-1500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-3500.0f,0.0f,-1500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-5500.0f,0.0f,-1500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-7500.0f,0.0f,-1500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(2500.0f,0.0f,-1500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(4500.0f,0.0f,-1500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(6500.0f,0.0f,-1500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(8500.0f,0.0f,-1500.0f), 9));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,-3000.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,-3000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,-3000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-6500.0f,0.0f,-3000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-8500.0f,0.0f,-3000.0f), 2));		
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,-3000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,-3000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(5500.0f,0.0f,-3000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(7500.0f,0.0f,-3000.0f), 4));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(500.0f,0.0f,-4500.0f), 5));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-1500.0f,0.0f,-4500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-3500.0f,0.0f,-4500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-5500.0f,0.0f,-4500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-7500.0f,0.0f,-4500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(2500.0f,0.0f,-4500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(4500.0f,0.0f,-4500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(6500.0f,0.0f,-4500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(8500.0f,0.0f,-4500.0f), 9));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,-6000.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,-6000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,-6000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-6500.0f,0.0f,-6000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-8500.0f,0.0f,-6000.0f), 2));		
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,-6000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,-6000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(5500.0f,0.0f,-6000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(7500.0f,0.0f,-6000.0f), 4));
	}

	void Setup15x15(double cellCycleTime, double attachmentForce)
	{
		Vector2D boundary(15500.0, 11500.0);
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,0.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,0.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,0.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-6500.0f,0.0f,0.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-8500.0f,0.0f,0.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-10500.0f,0.0f,0.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-12500.0f,0.0f,0.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-14500.0f,0.0f,0.0f), 1));				
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,0.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,0.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(5500.0f,0.0f,0.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(7500.0f,0.0f,0.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(9500.0f,0.0f,0.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(11500.0f,0.0f,0.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(13500.0f,0.0f,0.0f), 3));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(500.0f,0.0f,1500.0f), 5));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-1500.0f,0.0f,1500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-3500.0f,0.0f,1500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-5500.0f,0.0f,1500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-7500.0f,0.0f,1500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-9500.0f,0.0f,1500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-11500.0f,0.0f,1500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-13500.0f,0.0f,1500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(2500.0f,0.0f,1500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(4500.0f,0.0f,1500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(6500.0f,0.0f,1500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(8500.0f,0.0f,1500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(10500.0f,0.0f,1500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(12500.0f,0.0f,1500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(14500.0f,0.0f,1500.0f), 8));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,3000.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,3000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,3000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-6500.0f,0.0f,3000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-8500.0f,0.0f,3000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-10500.0f,0.0f,3000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-12500.0f,0.0f,3000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-14500.0f,0.0f,3000.0f), 1));				
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,3000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,3000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(5500.0f,0.0f,3000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(7500.0f,0.0f,3000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(9500.0f,0.0f,3000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(11500.0f,0.0f,3000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(13500.0f,0.0f,3000.0f), 3));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(500.0f,0.0f,4500.0f), 5));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-1500.0f,0.0f,4500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-3500.0f,0.0f,4500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-5500.0f,0.0f,4500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-7500.0f,0.0f,4500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-9500.0f,0.0f,4500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-11500.0f,0.0f,4500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-13500.0f,0.0f,4500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(2500.0f,0.0f,4500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(4500.0f,0.0f,4500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(6500.0f,0.0f,4500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(8500.0f,0.0f,4500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(10500.0f,0.0f,4500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(12500.0f,0.0f,4500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(14500.0f,0.0f,4500.0f), 8));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,6000.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,6000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,6000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-6500.0f,0.0f,6000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-8500.0f,0.0f,6000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-10500.0f,0.0f,6000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-12500.0f,0.0f,6000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-14500.0f,0.0f,6000.0f), 1));				
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,6000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,6000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(5500.0f,0.0f,6000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(7500.0f,0.0f,6000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(9500.0f,0.0f,6000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(11500.0f,0.0f,6000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(13500.0f,0.0f,6000.0f), 3));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(500.0f,0.0f,7500.0f), 5));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-1500.0f,0.0f,7500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-3500.0f,0.0f,7500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-5500.0f,0.0f,7500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-7500.0f,0.0f,7500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-9500.0f,0.0f,7500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-11500.0f,0.0f,7500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-13500.0f,0.0f,7500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(2500.0f,0.0f,7500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(4500.0f,0.0f,7500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(6500.0f,0.0f,7500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(8500.0f,0.0f,7500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(10500.0f,0.0f,7500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(12500.0f,0.0f,7500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(14500.0f,0.0f,7500.0f), 8));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,9000.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,9000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,9000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-6500.0f,0.0f,9000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-8500.0f,0.0f,9000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-10500.0f,0.0f,9000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-12500.0f,0.0f,9000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-14500.0f,0.0f,9000.0f), 1));				
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,9000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,9000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(5500.0f,0.0f,9000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(7500.0f,0.0f,9000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(9500.0f,0.0f,9000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(11500.0f,0.0f,9000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(13500.0f,0.0f,9000.0f), 3));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(500.0f,0.0f,10500.0f), 5));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-1500.0f,0.0f,10500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-3500.0f,0.0f,10500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-5500.0f,0.0f,10500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-7500.0f,0.0f,10500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-9500.0f,0.0f,10500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-11500.0f,0.0f,10500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-13500.0f,0.0f,10500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(2500.0f,0.0f,10500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(4500.0f,0.0f,10500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(6500.0f,0.0f,10500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(8500.0f,0.0f,10500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(10500.0f,0.0f,10500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(12500.0f,0.0f,10500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(14500.0f,0.0f,10500.0f), 8));
				
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(500.0f,0.0f,-1500.0f), 5));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-1500.0f,0.0f,-1500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-3500.0f,0.0f,-1500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-5500.0f,0.0f,-1500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-7500.0f,0.0f,-1500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-9500.0f,0.0f,-1500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-11500.0f,0.0f,-1500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-13500.0f,0.0f,-1500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(2500.0f,0.0f,-1500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(4500.0f,0.0f,-1500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(6500.0f,0.0f,-1500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(8500.0f,0.0f,-1500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(10500.0f,0.0f,-1500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(12500.0f,0.0f,-1500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(14500.0f,0.0f,-1500.0f), 8));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,-3000.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,-3000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,-3000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-6500.0f,0.0f,-3000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-8500.0f,0.0f,-3000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-10500.0f,0.0f,-3000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-12500.0f,0.0f,-3000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-14500.0f,0.0f,-3000.0f), 1));				
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,-3000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,-3000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(5500.0f,0.0f,-3000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(7500.0f,0.0f,-3000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(9500.0f,0.0f,-3000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(11500.0f,0.0f,-3000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(13500.0f,0.0f,-3000.0f), 3));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(500.0f,0.0f,-4500.0f), 5));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-1500.0f,0.0f,-4500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-3500.0f,0.0f,-4500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-5500.0f,0.0f,-4500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-7500.0f,0.0f,-4500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-9500.0f,0.0f,-4500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-11500.0f,0.0f,-4500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-13500.0f,0.0f,-4500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(2500.0f,0.0f,-4500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(4500.0f,0.0f,-4500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(6500.0f,0.0f,-4500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(8500.0f,0.0f,-4500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(10500.0f,0.0f,-4500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(12500.0f,0.0f,-4500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(14500.0f,0.0f,-4500.0f), 8));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,-6000.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,-6000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,-6000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-6500.0f,0.0f,-6000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-8500.0f,0.0f,-6000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-10500.0f,0.0f,-6000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-12500.0f,0.0f,-6000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-14500.0f,0.0f,-6000.0f), 1));				
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,-6000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,-6000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(5500.0f,0.0f,-6000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(7500.0f,0.0f,-6000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(9500.0f,0.0f,-6000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(11500.0f,0.0f,-6000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(13500.0f,0.0f,-6000.0f), 3));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(500.0f,0.0f,-7500.0f), 5));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-1500.0f,0.0f,-7500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-3500.0f,0.0f,-7500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-5500.0f,0.0f,-7500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-7500.0f,0.0f,-7500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-9500.0f,0.0f,-7500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-11500.0f,0.0f,-7500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-13500.0f,0.0f,-7500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(2500.0f,0.0f,-7500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(4500.0f,0.0f,-7500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(6500.0f,0.0f,-7500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(8500.0f,0.0f,-7500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(10500.0f,0.0f,-7500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(12500.0f,0.0f,-7500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(14500.0f,0.0f,-7500.0f), 8));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-500.0f,0.0f,-9000.0f), 0));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-2500.0f,0.0f,-9000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-4500.0f,0.0f,-9000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-6500.0f,0.0f,-9000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-8500.0f,0.0f,-9000.0f), 2));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-10500.0f,0.0f,-9000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-12500.0f,0.0f,-9000.0f), 1));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-14500.0f,0.0f,-9000.0f), 1));				
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(1500.0f,0.0f,-9000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(3500.0f,0.0f,-9000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(5500.0f,0.0f,-9000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(7500.0f,0.0f,-9000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(9500.0f,0.0f,-9000.0f), 3));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(11500.0f,0.0f,-9000.0f), 4));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(13500.0f,0.0f,-9000.0f), 3));

		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(500.0f,0.0f,-10500.0f), 5));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-1500.0f,0.0f,-10500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-3500.0f,0.0f,-10500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-5500.0f,0.0f,-10500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-7500.0f,0.0f,-10500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-9500.0f,0.0f,-10500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-11500.0f,0.0f,-10500.0f), 7));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(-13500.0f,0.0f,-10500.0f), 6));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(2500.0f,0.0f,-10500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(4500.0f,0.0f,-10500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(6500.0f,0.0f,-10500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(8500.0f,0.0f,-10500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(10500.0f,0.0f,-10500.0f), 8));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(12500.0f,0.0f,-10500.0f), 9));
		crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, boundary, normalRNG, Vector3D(14500.0f,0.0f,-10500.0f), 8));
	}

	/**********************************************************************************

	Initialises the simulation, sets up the crypts and cells and various parameters for
	modelling mutation effects.
	
	**********************************************************************************/
	bool InitSimulation()
	{

		MutationData noMutation = { false, false, false };
		MutationData g0Mutation = { true, false, false };
		MutationData adhesionMutation = {false, true, false };
		MutationData cellForceMutation = {false, false, true };
		MutationData mutateAPC = { true, true, true };
		MutationData mutateAPCNonAdhesive = {true, false, true };

		SimSetup* settings = new SimSetup[125];

		unsigned numSettings = 625;

		char* env = getenv("SGE_TASK_ID");

		std::stringstream stream;
	
		int seed = time(NULL);
		if(env)
		{
			unsigned taskId = 0;

			stream << env;
			stream >> taskId;

			taskId--;

			double quiescenceMultipliers[] = { 1.0, 0.75, 0.5, 0.25, 0.1};
			double adhesionMultipliers[] = {1.0, 2.5, 5.0, 7.5, 10.0};
			double forceMultipliers[] = {1.0, 1.25, 1.5, 1.75, 2.0};

			if(taskId < numSettings)
			{
				// time() resolution is really poor so need to make sure that repeats don't have the same seed.
				seed += taskId;

				for(int i = 0; i < 5; i++)
				{
					for(int j = 0; j < 5; j++)
					{
						for(int k = 0; k < 5; k++)
						{
							MutationData mutation = {true, true, true, quiescenceMultipliers[i], adhesionMultipliers[j], forceMultipliers[k]};
							
							if(i == 0)
							{
								mutation.mutateQuiecence = false;
							}
							if(j == 0)
							{
								mutation.mutateAttachment = false;
							}
							if(k == 0)
							{
								mutation.mutateCellForces = false;
							}

							std::stringstream name;
							name << "data/Q" <<  mutation.quiesceneceMultiplyer	<< "AF" << mutation.attachmentMultiplyer << "CF" << mutation.cellForceMultiplier;
							SimSetup setting =  { 108000,0.001, name.str(), mutation};
							settings[i + j * 5 + k * 25] =  setting;

						}
					}
				}
				int numRepeats = 5;

				currentSettings = settings[taskId / numRepeats];
				std::stringstream tempName;
				tempName << currentSettings.filename << "Run" << taskId % numRepeats << ".csv";
				currentSettings.filename = tempName.str();
				filename = currentSettings.filename;
				
				double cellCycleTime = settings[taskId].averageGrowthTimeInSeconds;
				double attachmentForce = settings[taskId].membraneAttachmentForce;

				double secondsPerTimestep = 30.0;
				normalRNG = new NormalDistributionRNG(cellCycleTime / secondsPerTimestep, 2.625 * 3600.0 / secondsPerTimestep);

				Setup5x5(cellCycleTime, attachmentForce);

				for(int i = 0; i < crypts.size(); i++)
				{
					for(int j = i + 1; j < crypts.size(); j++)
					{
						crypts[i]->m_grid.SetupCollisionWithOtherGrid(crypts[j]->m_grid);
					}
				}

				Simulation::crypts.begin();

				srand(seed);
				return true;
			}
		}

		return false;
	}

	void MeasureMutationSpread(double& distance, Vector3D mutationOrigin, int& cryptInvasion)
	{
		distance = 0;
		cryptInvasion = 0;

		for(int cryptId = 0; cryptId < crypts.size(); cryptId++)
		{
			Crypt* crypt = crypts[cryptId];
			for(int col = 0; col < (int)crypt->m_grid.m_columns.size(); col++)
			{
				std::vector<CellBox>& column = crypt->m_grid.m_columns[col];
				for(int row = 0; row < (int)column.size(); row++)
				{
					CellBox& box = column[row];
					for(int cell = 0; cell < box.m_positions.size(); cell++)
					{
						Vector2D delta = Vector2D(box.m_positions[cell].x, box.m_positions[cell].z);
						delta.x -= mutationOrigin.x;
						delta.y -= mutationOrigin.z;

						double cellDistance = delta.Length();

						if(cellDistance > distance && 
							(box.m_mutations[cell].mutateAttachment == true || box.m_mutations[cell].mutateCellForces == true || box.m_mutations[cell].mutateQuiecence == true))
						{
							distance = cellDistance;
							if(distance > 1000.0 && box.m_positions[cell].y < crypt->m_cryptHeight / -4)
							{
								cryptInvasion++;
							}
						}
					}
				}
			}
		}
	}

	void DoMutation(int cryptToMutate)
	{
		float minDelta = 100000.0; // Sufficiently big number, ie bigger than a crypt
		CellBox* closestBox = NULL;
		int closestCell = 0;

		for(int i = 0; i <1; i++)
		{
			for(int col = 0; col < (int)crypts[cryptToMutate]->m_grid.m_columns.size(); col++)
			{
				std::vector<CellBox>& column = Simulation::crypts[cryptToMutate]->m_grid.m_columns[col];
				for(int row = 0; row < (int)column.size(); row++)
				{
					CellBox& box = column[row];
					for(int cell = 0; cell < box.m_positions.size(); cell++)
					{
						Vector3D& vec = box.m_positions[cell];
						float delta = fabs((vec.y + crypts[cryptToMutate]->m_cryptHeight) - mutationHeight);

						if(delta < minDelta)
						{
							minDelta = delta;
							closestBox = &box;
							closestCell = cell;
						}
					}
				}
			}
		}
		closestBox->m_mutations[closestCell] = currentSettings.mutationData;
	}

	/*************************************************************************

	In a multi-crypt simulation cells can move from one crypt to another, this
	function detects if a cell has migrated and copies it into the new crypt
	then deletes it from the old crypt.

	*************************************************************************/
	void AssignCellsToCrypts()
	{
		for(int i = 0; i < Simulation::crypts.size(); i++)
		{
			Crypt* currentCrypt = Simulation::crypts[i];
			CylindricalGrid& grid = currentCrypt->m_grid;

			for(int col = 0; col < (int)grid.m_columns.size(); col++)
			{
				std::vector<CellBox>& column = grid.m_columns[col];
				for(int row = 0; row < (int)column.size(); row++)
				{
					CellBox& box = column[row];
					for(int cellId = 0; cellId < (int)box.m_positions.size(); cellId++)
					{
						Vector3D cellPos = box.m_positions[cellId];
						Vector3D currentDelta = cellPos - currentCrypt->m_pos;
						currentDelta.y = 0.0;
						float currentDist = currentDelta.Length();
						int closestCrypt = -1;

						for(int j = 0; j < Simulation::crypts.size(); j++)
						{
							Vector3D testDelta = cellPos - Simulation::crypts[j]->m_pos;
							testDelta.y = 0.0;
							float testDist = testDelta.Length();

							if(testDist < currentDist)
							{
								currentDist = testDist;
								closestCrypt = j;
							}
						}
						if(closestCrypt != -1)
						{
							CellBox* newBox = Simulation::crypts[closestCrypt]->m_grid.FindBox(cellPos);
							if(newBox != &box)
							{
								int id = newBox->CopyCell(box, cellId);
								int oldCrypt = box.m_originCrypts[cellId];
								box.RemoveCell(cellId);
								newBox->m_originCrypts[id] = oldCrypt;
								cellId--;
							}
						}
					}
				}
			}
		}
	}

	/******************************************************************

	The main update function for the simulation.  Update all crypts
	then handle any cells that have migrated from one crypt to another.

	******************************************************************/
	void StepSimulation(int timestep)
	{
		for(int i = 0; i< Simulation::crypts.size(); i++)
		{
			crypts[i]->Step(timestep);
		}
		AssignCellsToCrypts();
	}

	void CleanUpSimulation()
	{
		delete normalRNG;
		for(int i = 0; i < crypts.size(); i++)
		{
			delete crypts[i];
		}
	}
};
