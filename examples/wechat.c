#include <stdio.h>
#include <string.h>
#include "mongoose.h"
#include "stdlib.h"

struct mg_server *server;

// This function will be called by mongoose on every new request
static int websocket_user_handler(struct mg_connection *conn) {
	char *buf = NULL;
	buf = malloc(conn->content_len+1);
	memcpy(buf, conn->content, conn->content_len);
	buf[conn->content_len] = '\0';

	if ((conn->wsbits & 0xf) != 0xa)	/*skip ping/pong message*/
	{
		mg_websocket_broadcast_message(server, (void *)&buf);
	}

	free(buf);

	return 0;
}

int main(void) {
  // Create and configure the server
  server = mg_create_server(NULL);
  mg_set_option(server, "listening_port", "8080");
  mg_set_option(server, "document_root", ".");
  mg_add_uri_handler(server, "/sock", websocket_user_handler);

  // Serve request. Hit Ctrl-C to terminate the program
  printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
  for (;;) {
    mg_poll_server(server, 1000);
  }

  // Cleanup, and free server instance
  mg_destroy_server(&server);

  return 0;
}
