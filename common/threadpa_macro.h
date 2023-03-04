/** 
* @brief: THREADPA_INIT(()- Initial p_thread struct
* @name: Thread struct name
* @type: Element#1 of Thread struct
* @name_type: Indicate the name of Element#1 of Thread struct
* @input:  Indicate the name of Element#2 of Thread struct
*/
#define THREADPA_INIT(name,type, name_type, input) \
        threadpa_t name; \
        name.type=name_type; \
        name.node=input; 
