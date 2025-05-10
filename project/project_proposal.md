# Project Proposal

The course project I have in mind will be the project I am currently 
working on for my Master's research with Prof. Hunter Belanger. This
project is to implement CMFD (coarse mesh finite difference) acceleration in his MOC (method of characteristics) code Scarabee. The overview of this project is given below. 

## Scarabee

Scarabee is a lattice physics code for light water nuclear reactors. One of its features is the ability to solve 2D fixed-source and k-eigenvalue problems using the method of characteristics to solve the neutron transport equation in energy, space, and angle for a given geometry and set of material compositions. A detailed overview of the method of characteristics theory can be found at:
https://mit-crpg.github.io/OpenMOC/methods/method_of_characteristics.html


## CMFD 

CMFD acceleration is a method to greatly increase the speed of convergence of MOC solvers. In CMFD, the fine mesh is collapsed to a rectilinear coarse mesh and the neutron balance is preserved exactly in each cell. The geometrical information such as cell boundaries and segement surface crossings are generated only once, at the beginning of the simulation. On each iteration (or nth iteration) of the MOC transport solve, the currents are tallied on each CMFD cell surface. This information is used to solve the coarse mesh diffusion problem directly after the MOC solve. Once the diffusion problem has converged, the scalar flux of each MOC flat source region (FSR) (the fine mesh regions) will be updated by the ratio of the converged coarse mesh scalar flux to the initial coarse mesh scalar flux in the cell which contains that FSR. 