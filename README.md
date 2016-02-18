# stoplight
This is a fork of a project that I was working on in Computer Science 2. I adapted it to use Finite State Machines, something
which I hadn't done in the project for class. To do this, I used an enum variable with five possible states and a switch to alternate
between them. The state-switcher runs with variable delta timing where each state chooses its own deltaTime, allowing for different states
to have different timing. Like any program with delta timing, it needs to be reset every 50 days so the unsigned long doesn't rollover.
This is just a demonstrator, though so I doubt anyone will run it that long.
