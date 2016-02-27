typedef struct server_info{
		int cost;
		char server_name[1026];
	}server_info_node;

typedef struct server_list{
		int num_servers;
		struct server_info *obj;
		struct server_list *next;
	}server_list_obj;
