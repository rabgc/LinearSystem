# Linear System 

# Code is under development,  Not ready for use. 

The LinearSystem class is intended to serve two types of application: 
discrete sequential state estimation (DSE), and batched linear regression (BLR). These standard problem types were used to guide the development of LinearSystem, but of course the user has complete contol of how the system matrices are utilized. 
 
## Assumptions
For DSE, observations are assumed to represent measurements of a state variable at a single epoch of time. Observations are associated to targets and each 
target is represented by its own state vector.  The parameters of the state
vector depend on the physical dimensions of the system and the order of the 
system dynamics equation. The *state* typically comprises positional 
coordinates of the targets and the target's velocity. The *observations* typically consist of target position estimates, but may 
also include velocity estimates. Higher order dynamics are not supported in 
the current implementation, but may be added in the future.  

A state transition matrix can be created to propagate the state vector 
from one epoch to the next for use in a Kalman filter or similar sequential 
estimator. LinearSystem could also be extended to build control input 
matrices in support target tracking and control, but control matrices are not currently implemented.

LinearSystem may also be used to build the design matrix for BLR models, in 
which all data are to be used simultaneously to solve for model parameters. 
For this application, set equate_targets to enfore the condition that all 
data points represent redundant measurements of the same target variable. 
The num_targets then determines the length of the data vector.  All other 
inputs should assume default values. In this case, the design matrix is 
built from a bias column, and the state vector is simply the model 
parameter vector associated to the target variable. The dimensions of the 
parameter vector depend on how many additional feature columns are added 
to the design matrix. The target-state vector terminology is retained 
throughout LinearSystem for consistency, even though the regression 
variables may not represent physical states. LinearSystem can also contruct 
regularization matrices. 

For either application, the design matrix is instantiated as a simple bias, 
but additional feature columns may be added. The LinearSystem class also 
provides methods for generating process and measurement noise covariance 
matrices, as well as the a priori state covariance and state estimate.




