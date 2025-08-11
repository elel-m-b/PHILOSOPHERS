/*
						-idea : deadlock 
If philo ID is even → lock right fork first, then left fork.

If philo ID is odd → lock left fork first, then right fork.


tips ::
	Your usleep is just a timing trick — it staggers when philosophers start eating, so in real runs you might avoid deadlock.

	But Helgrind doesn’t care about timing.
	It’s not checking “did you deadlock?” — it’s checking “is there any possible code path where two locks are acquired in different orders?”.

*/