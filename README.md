# Linear System 

# Code is under development,  Not ready for use. 

The LinearSystem class is intended to generate system matrices in service of two types of application: discrete sequential state estimation (DSE), and batched linear regression (BLR). These standard problem types were used to guide the development of LinearSystem, but of course the user has complete contol of how the system matrices are utilized. 
 
## Assumptions for DSE
For DSE, observations are assumed to represent measurements of a state variable at a single epoch of time. Observations are associated to targets and each 
target is represented by its own state vector. The parameters of the state
vector depend on the physical dimensions of the system and the order of the 
system dynamics equation. The *state* typically comprises coordinates of the targets and their rates of change. The *observations* typically consist of target coordiante estimates only, but may also include rate estimates. 

A state transition matrix can be created to propagate the state vector 
from one epoch to the next for use in a sequential estimator. LinearSystem could also be extended to build control input matrices in support target tracking and control, but control matrices are not currently implemented.

## Assumptions for BLR
LinearSystem may also be used to build the design matrix for BLR models, in 
which all data are to be used simultaneously to solve for model parameters. 
For this application, set equate_targets=true to enfore the condition that all 
data points represent redundant measurements of the same target variable. 
The num_targets then determines the length of the data vector. All other 
inputs should assume default values (where defualts are provided). In this case, the design matrix is built from a bias column, and the state vector is simply the model parameter vector associated to the target variable. The dimensions of the parameter vector depend on how many additional feature columns are added to the design matrix. The target-state vector terminology is retained throughout LinearSystem for consistency, even though the regression 
variables may not represent physical states. LinearSystem can also construct 
regularization matrices. 

## Noise and model estimate covariance matrices 
The LinearSystem class also provides methods for generating process and measurement noise covariance matrices, as well as the a priori state covariance and state estimate.




