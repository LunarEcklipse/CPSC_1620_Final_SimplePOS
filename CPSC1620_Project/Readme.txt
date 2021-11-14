This was a fairly ambitious project. I apologize for it's size. I look forward to hearing your feedback!

This ultimately is a fairly unintuitive interface and would work better as a visual interface, but I haven't learned how to make those yet.

You'll find a list of commands in commands.cpp in the comments.

You can edit the data files as well to change up the data or break the program entirely if you'd like. I've included an example file for you to use.

In case you're unsure, the password is "admin" (no quotes).

Finally, there are 4 compiler warnings you'll notice (at least with Visual Studio 2019). This is all because I ignored the return values of _getch()
in multiple places since I just wanted the press key functionality. I understand if you ding me for this because you did say it is ideal to work out compiler
warnings entirely, but if I were to do so, I would just create an int variable (like "int dummy") to absorb the incoming value and then discard it anyways by using
scope ({ }).