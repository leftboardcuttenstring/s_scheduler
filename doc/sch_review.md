# What interfaces does SCH give to ya?
The main structure for creating the task  
Two main functions - `dispatch` and `presetting` for process the task
and prepare the environment for it's executing  
The main function for connecting the central object with your `dispatch`
and `presetting` function's implementations - `sch_task_create` that
function is