To do:

Change file parsing -> do it massively

Done:

Use hashing for checking for duplicates in graph
We need compact neighbor arrays
Use memcpy for Queue







Planning the job scheduling:

We'll need:
	scheduler mutex
	scheduler condition

	ONE worker condition
	MANY worker mutexes

	jobsFinished variable
	totalWorkers variable

///////////////////////////////////////////////////////////////////////////////////////


Workers:

my_mutex_down
scheduler_mutex_down
	Increase finishedJobs var
	if(all_executed == true) {		// Ensure that all workers are initialized
  		send scheduler_cond
	}
scheduler_mutex_up

LOOP!

	cond_wait (my_mutex_tmp_release)	// mutex is ALWAYS LOCKED apart from this part

	if(STOP) {
		Exit LOOP
	}
	Execute ALL (LOOP2)

	scheduler_mutex_down
		Increase finishedJobs var
		if(all_executed == true) {
	  		send scheduler_cond
		}
	scheduler_mutex_up

my_mutex_up

///////////////////////////////////////////////////////////////////////////////////////


Scheduler:

scheduler_mutex_down
init threads
cond_wait (scheduler_mutex_up)		// Wait initialization of all threads

LOOP!

	give jobs

	All worker mutexes down (to ensure that all of them are unlocked by the cond)
		signal all workers to start (broadcast condition)
	All worker mutexes up

	cond_wait (scheduler_mutex_up)	// mutex is ALWAYS LOCKED apart from this part
	initialise all workers

GIVE STOP JOB TO EVERY ONE!
scheduler_mutex_up






