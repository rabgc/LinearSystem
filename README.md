# Linear System 

### Code is under development. Not ready for use. 

The LinearSystem class is intended to generate system matrices in service of two types of application: discrete sequential state estimation (DSE), and batched linear regression (BLR). These standard problem types were used to guide the development of LinearSystem, but of course the user has complete control over how the system matrices are utilized. 

## State and Target Vector Organization

The LinearSystem class uses a **target-based partitioning scheme** for the state vector. This means:

- The state vector is organized as a concatenation of each target's state vector.
- For `num_targets` targets, each with a state vector of length `target_state_len`, the full state vector is:

  ```
  [target1_state, target2_state, ..., targetN_state]
  ```

- Each `target_state` is itself a concatenation of parameter types (e.g., position, velocity, [acceleration], ...) for that target, in the order determined by `system_order` and `physical_dim`.

  For example, with `system_order=2` (position and velocity) and `physical_dim=3` (3D), each target's state vector is:

  ```
  [pos_x, pos_y, pos_z, vel_x, vel_y, vel_z]
  ```

- The full state vector for two targets would be:

  ```
  [t1_pos_x, t1_pos_y, t1_pos_z, t1_vel_x, t1_vel_y, t1_vel_z,
   t2_pos_x, t2_pos_y, t2_pos_z, t2_vel_x, t2_vel_y, t2_vel_z]
  ```

- All system matrices (state transition, design, noise covariance, etc.) are constructed to be consistent with this partitioning.

**Note:**  
If you use features or options that change the state vector layout, refer to the relevant documentation or code comments for details.

## Assumptions for DSE
For DSE, observations are assumed to represent measurements of a state variable at a single epoch of time. Observations are associated with targets and each 
target is represented by its own state vector. The parameters of the state
vector depend on the physical dimensions of the system and the order of the 
system dynamics equation. The *state* typically comprises coordinates (or coordinate adjustments) of the targets and their rates of change. The *observations* typically consist of target coordinate (or coordinate adjustment) estimates only, but may also include rate estimates. 

A state transition matrix can be created to propagate the state vector 
from one epoch to the next for use in a sequential estimator. LinearSystem could also be extended to build control input matrices in support of target tracking and control, but control matrices are not currently implemented.

## Assumptions for BLR
LinearSystem may also be used to build the design matrix for BLR models, in 
which all data are to be used simultaneously to solve for a vector of model parameters. 
For this application, set `equate_targets=true` to enforce the condition that all 
data points represent redundant measurements of the same target variable. 
The `num_targets` then determines the length of the data vector. All other 
inputs should assume default values (where defaults are provided). In this case, the design matrix is built from a bias column, and the state vector is simply the model parameter vector associated with the target variable. The dimensions of the parameter vector depend on how many additional feature columns are added to the design matrix. The target-state vector terminology is retained throughout LinearSystem for consistency, even though the regression 
variables may not represent physical states. 

## Regularization
LinearSystem can also construct regularization matrices for Tikhonov or ridge regression. 

## Noise and model estimate covariance matrices 
The LinearSystem class also provides methods for generating process and measurement noise covariance matrices, as well as the a priori state covariance and state estimate.




