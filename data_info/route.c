#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

#include "route.h"
#include "../utlist.h"

di_route_el_t *route_get(di_route_list_t *list, di_prefix_t route_prefix, bool allow_summary) {
	di_route_el_t *route;
	
	LL_FOREACH(*list, route) {
		if(route_prefix.length == route->route_prefix.length && !addr_compare_ip_len(&route->route_prefix.prefix, &route_prefix.prefix, route_prefix.length))
			return route;
	}
	
	return NULL;
}

di_route_el_t *route_add(di_route_list_t *list, di_prefix_t route_prefix, bool auto_summary, bool *was_already_existing) {
	di_route_el_t *route;
	
	LL_FOREACH(*list, route) {
		if(route_prefix.length == route->route_prefix.length && !addr_compare_ip_len(&route->route_prefix.prefix, &route_prefix.prefix, route_prefix.length)) {
			if(was_already_existing) *was_already_existing = true;
			return route;
		}
	}
	
	route = (di_route_el_t*) calloc(1, sizeof(di_route_el_t));
	route->route_prefix = route_prefix;
	LL_PREPEND(*list, route);
	
	if(was_already_existing) *was_already_existing = false;
	return route;
}

bool route_remove(di_route_list_t *list, di_prefix_t route_prefix) {
	di_route_el_t *route;
	
	LL_FOREACH(*list, route) {
		if(route_prefix.length == route->route_prefix.length && !addr_compare_ip_len(&route->route_prefix.prefix, &route_prefix.prefix, route_prefix.length)) {
			LL_DELETE(*list, route);
			free(route);
			return true;
		}
	}
	
	return false;
}

bool route_del_all_outdated(di_route_list_t *list) {
	return false;
}

di_route_list_t route_dup(di_route_list_t *routes) {
	di_route_list_t new_routes = NULL;
	di_route_el_t *route, *new_route, *last_route;
	
	last_route = NULL;
	LL_FOREACH(*routes, route) {
		new_route = (di_route_el_t*) malloc(sizeof(di_route_el_t));
		memcpy(new_route, route, sizeof(di_route_el_t));
		if(last_route)
			last_route->next = new_route;
		new_route->next = NULL;
		if(new_routes == NULL)
			new_routes = new_route;
		last_route = new_route;
	}
	
	return new_routes;
}
