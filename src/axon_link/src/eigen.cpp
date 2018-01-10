#include <iostream>
#include <Eigen/Dense>
#include <cmath>
using Eigen::MatrixXd;
int main()
{
  double radius, lengthToCenter, paramA, paramB;
  radius = 5;
  paramA = 1/sqrt(3);
  paramB = 1/sqrt(9);
  lengthToCenter = 26.3;
  MatrixXd m(3,3);
  MatrixXd c(3,1);
  MatrixXd e(3,1);
  c(0,0) = 1;
  c(1,0) = 2;
  c(2,0) = 3;
  m(0,0) = 1/3;
  
  m(0,1) = -paramA*radius;
  m(0,2) = paramA*radius;
  m(1,0) = -2*paramB*radius;
  m(1,1) = paramB*radius;
  m(1,2) = paramB*radius; 
  m(2,0) = radius*paramB/lengthToCenter;
  m(2,1) = radius*paramB/lengthToCenter;
  m(2,2) = radius*paramB/lengthToCenter;
  std::cout << m.inverse() << std::endl;
  e = m.inverse() * c;
  std::cout << e << std::endl;

  std::cout << c << std::endl;
}