1. In this assignment I suggested you use `fgets()` to get user input in the main while loop. Why is `fgets()` a good choice for this application?

    > **Answer**: 'fgets()' is a good choice because it reads the input line by line. This makes it easy to process all shell commands, and this also handles our buffer overflow by limiting the number of characters read.

2. You needed to use `malloc()` to allocate memory for `cmd_buff` in `dsh_cli.c`. Can you explain why you needed to do that, instead of allocating a fixed-size array?

    > **Answer**: Using 'malloc()' allows us to dynamically allocate memory for our buffer at runtime. However, I was able to run my code without using 'malloc()'. The reason for this is because within dshlib.h, 'SH_CMD_MAX' is defined which is our predefined max command size. I can see how 'malloc()' would be useful, but instead of using it, I decided to clear the command buffer using 'memset()' which allowed me to compare the command buffer to the max command size.

3. In `dshlib.c`, the function `build_cmd_list()` must trim leading and trailing spaces from each command before storing it. Why is this necessary? If we didn't trim spaces, what kind of issues might arise when executing commands in our shell?

    > **Answer**: Trimming spaces is necessary to in order to make sure that arguments and commands are parsed correctly, respectively. If we did not trim spaces, it could lead to execution errors as well as parsing errors.


4. For this question you need to do some research on STDIN, STDOUT, and STDERR in Linux. We've learned this week that shells are "robust brokers of input and output". Google _"linux shell stdin stdout stderr explained"_ to get started.

- One topic you should have found information on is "redirection". Please provide at least 3 redirection examples that we should implement in our custom shell, and explain what challenges we might have implementing them.

    > **Answer**: 
    > 1. `command > file`: Runs the command and redirects the output(stdout) to  the file | Challenge: Handling file permissions(rwx) and ensuring the file is created or overwritten correctly.
    > 2. `command < file`: Takes the content of the file as input for the given command. | Challenge: Ensuring the file exists(is readable 'r') and is readable.
    > 3. `command 2> file`: Runs the command and redirects the error messages(stderr) to the file | Challenge: Differentiating between STDOUT and STDERR streams, so making sure we handle our output and error messages correctly.

- You should have also learned about "pipes". Redirection and piping both involve controlling input and output in the shell, but they serve different purposes. Explain the key differences between redirection and piping.

    > **Answer**: Redirection is used to redirect input or output to or from a file. Pipes are used to connect the output of a command to the input of another command.
    

- STDERR is often used for error messages, while STDOUT is for regular output. Why is it important to keep these separate in a shell?

    > **Answer**: Keeping STDERR and STDOUT seperated is important because it allows users/people who work with/on the shell to distinguish between regular output and error messages. This allows for better error handling and debugging.
    

- How should our custom shell handle errors from commands that fail? Consider cases where a command outputs both STDOUT and STDERR. Should we provide a way to merge them, and if so, how?

    > **Answer**: Our custom shell should print both the STDOUT and STDERR messages. We can also include a way to merge them by using 2>&1 which redirects stderr to the same place as stdout. This would allow the users to see the output and error messages in a single stream.