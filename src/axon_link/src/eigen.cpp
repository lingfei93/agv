#include <iostream>
#include <Eigen/Dense>
#include <cmath>
using Eigen::MatrixXd;
int main()
{
  double radius, lengthToCenter, paramA;
  radius = 5;
  paramA = 1/sqrt(3);
  lengthToCenter = 26.3;
  MatrixXd m(3,3);
  m(0,0) = 3;
  
  m(0,1) = -1;
  m(0,2) = 0;
  m(1,0) = 2.5;
  m(1,1) = m(1,0) + m(0,1);
  m(1,2) = 0; 
  m(2,0) = 0;
  m(2,1) = 0;
  m(2,2) = 0;
  std::cout << m << std::endl;
}