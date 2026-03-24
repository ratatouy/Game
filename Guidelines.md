# Documentation and Style Guidelines :

# Part 1 - Documentation Guidelines :

## ".hpp" files :

- Use triple backslashes "///" for documentation.
- Use backslashes for every annotation type.
- All sentences must start with an uppercase letter.
- Skip lines between every annotations.
- Place this block before the includes :
```
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
```


### Classes :
- Surround the documentation by backslashes (usually 60 above and 60 below)
- Place the documentation above the declaration.
- Notify the type of the annotation at **every** comment except for "\details".
- There must be a "\brief" annotation.


### Functions and Methods :
- All the rules for "Classes apply.
- Place a "\param" annotation per argument.
- Place a "\returns" annotation if the return type isn't void nor is it a constructor.


### Variables and Attributes :
- Place the comment below the declaration, it can be on the same line if the comment is small enough.
- Notifying the type of annotation isn't necessary if the comment is small enough.


#### Example :
```
////////////////////////////////////////////////////////////
/// \brief A brief description.
///
/// I am currently going into further details of what
/// the function does but I don't have much to say so 
/// I will just stop there, have a nice day !
///
/// \param var the input variable
///
/// \returns int the result
////////////////////////////////////////////////////////////
int foo(float var);
```

## ".cpp" files :
- Use double backslashes.


# Part 2 - Style Guidelines :
- Place a ";" at the end of non-defined function declarations in header files.
- Don't indent "public", "protected" or private", same for the code it applies to.
- Place Member data of a class **after** the Methods.