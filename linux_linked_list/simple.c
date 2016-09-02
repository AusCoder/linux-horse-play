#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

/* this is the birthday struct */
struct birthday {
        int day;
        int month;
        int year;
        struct list_head list;
};

/* initialise the birthday list */
static LIST_HEAD(birthday_list);

/* This function is called when the module is loaded. */
int simple_init(void)
{

        struct birthday *seb;
        struct birthday *bill;
        struct birthday *lui;
        struct birthday *ptr;

        printk(KERN_INFO "Loading Module\n");

        /* define some birthdays and add them to the list */
        seb = kmalloc(sizeof(*seb), GFP_KERNEL);
        seb->day = 6;
        seb->month = 8;
        seb->year = 1991;
        INIT_LIST_HEAD(&seb->list);

        /* the raw pointer manipulation */
        ((&birthday_list)->prev)->next = &seb->list;
        (&seb->list)->next = &birthday_list;
        (&seb->list)->prev = (&birthday_list)->prev;
        (&birthday_list)->prev = &seb->list;
        //list_add_tail(&seb->list, &birthday_list);
        /*
         * struct list_head
         * has next and prev attributes
         * next/prev have type struct list_head *
         */

        bill = kmalloc(sizeof(*bill), GFP_KERNEL);
        bill->day = 2;
        bill->month = 5;
        bill->year = 1980;
        INIT_LIST_HEAD(&bill->list);
        
        /* raw pointer manipulation */
        ((&birthday_list)->prev)->next = &bill->list;
        (&bill->list)->next = &birthday_list;
        (&bill->list)->prev = (&birthday_list)->prev;
        (&birthday_list)->prev = &bill->list;
        //list_add_tail(&bill->list, &birthday_list);

        lui = kmalloc(sizeof(*lui), GFP_KERNEL);
        lui->day = 25;
        lui->month = 9;
        lui->year = 1900;
        INIT_LIST_HEAD(&lui->list);
        
        /* raw pointer manipulation */
        ((&birthday_list)->prev)->next = &lui->list;
        (&lui->list)->next = &birthday_list;
        (&lui->list)->prev = (&birthday_list)->prev;
        (&birthday_list)->prev = &lui->list;
        //list_add_tail(&lui->list, &birthday_list);


        /* iterate through the list of birthdays */
        for (ptr->list = *(birthday_list.next); \
                        &ptr->list != &birthday_list; \
                        ptr->list = *((ptr->list).next) ) {
               printk(KERN_INFO "birth year: %d", ptr->year);
        }

        /*
       list_for_each_entry(ptr, &birthday_list, list) {
               printk(KERN_INFO "birth year: %d", ptr->year);
       }
       */

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {

        struct birthday *ptr, *next;

	printk(KERN_INFO "Removing Module\n");

        /* delete the list */

        list_for_each_entry_safe(ptr, next, &birthday_list, list) {
                list_del(&ptr->list);
                kfree(ptr);
        }
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

