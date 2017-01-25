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

	Execute
	if(STOP) {
		scheduler_mutex_up
		terminate
	}

	scheduler_mutex_down
		Increase finishedJobs var
		if(all_executed == true) {
	  		send scheduler_cond
		}
	scheduler_mutex_up


///////////////////////////////////////////////////////////////////////////////////////


Scheduler:

scheduler_mutex_down
init threads
cond_wait (scheduler_mutex_up)		// Wait initialization of all threads

LOOP!

	give jobs
	if(STOP) GIVE TO EVERY ONE!

	All worker mutexes down (to ensure that all of them are unlocked by the cond)
		signal all workers to start (broadcast condition)
	All worker mutexes up

	if(!STOP)
		cond_wait (scheduler_mutex_up)	// mutex is ALWAYS LOCKED apart from this part

scheduler_mutex_up






