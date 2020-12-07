#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/kthread.h>
#include<linux/slab.h>
#include<linux/delay.h>

int i=0,j=0;
int foo(void *_arg)
{
	//compare and swap
	__sync_val_compare_and_swap(&i,i,++i);

	//fetch_and_add
	//__sync_fetch_and_add(&i,1);
	
	//test_and_set
	//__sync_lock_test_and_set(&i,++i);

	return 0;
}
int foo1(void *_arg)
{
	j++;
	return 0;
}




void thread_create(void)
{
	int argN=23;
	int *arg=&argN; 
	printk("start i: %d\t j: %d\n",i,j);
	kthread_run(&foo,(void*)arg,"foo");
	kthread_run(&foo1,(void*)arg,"foo1");
	printk("K1 i: %d\t j: %d\n",i,j);
	kthread_run(&foo,(void*)arg,"foo");
	kthread_run(&foo1,(void*)arg,"foo1");
	printk("K2 i: %d\t j: %d\n",i,j);
	kthread_run(&foo,(void*)arg,"foo");
	kthread_run(&foo1,(void*)arg,"foo1");
	printk("K3 i: %d\t j: %d\n",i,j);
	kthread_run(&foo,(void*)arg,"foo");
	kthread_run(&foo1,(void*)arg,"foo1");
	printk("K4 i: %d\t j: %d\n",i,j);
	printk("final : %d\t j: %d\n",i,j);

}


int __init hello_module_init(void)
{
	thread_create();
	printk(KERN_EMERG "Hello Simple Module!\n");
	return 0;
}

void __exit hello_module_cleanup(void)
{
	printk("Bye Module!\n");
}

module_init(hello_module_init);
module_exit(hello_module_cleanup);

MODULE_LICENSE("GPL");
