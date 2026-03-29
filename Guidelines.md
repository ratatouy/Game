# Documentation and Style Guidelines :

# Part 1 - Documentation Guidelines :

## ".hpp" files :

- Use triple backslashes "///" for documentation.
- Use backslashes for every annotation type.
- All sentences must start with an uppercase letter.
- Skip lines between every annotations.
- Place this block before the includes :
```c++
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
```


### General Guidelines :
- Surround the documentation by backslashes (60 above and 60 below)
- Place the documentation above the declaration.
- Notify the type of the annotation at **every** comment except for _"\details"_ (don't put details).
- There must be **at least** a _"\brief"_ annotation for every function.
  
### Classes :
- __INHERITANCE__ (without doc):
  - Use only one of ```virtual override``` per declaration :  
```c++
class A {
    virtual void foo() {} 
};

class B : public A{
    void foo() override
};

class C : public B {
	void foo() override
};
```
- Don't use ```final``` as it doesn't do much and prevents extending the code further (modders too)

### Functions and Methods :
- Place a "\param" annotation per argument.
- Place a "\returns" annotation if the return type isn't void nor is it a constructor.

#### Example :
```c++
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

### Variables and Attributes :
- Place the comment below the declaration, it can be on the same line if the comment is small enough.
- Notifying the type of annotation isn't necessary if the comment is small enough.
- For class attributes use this format :
```c++
////////////////////////////////////////////////////////////
/// Member Data
////////////////////////////////////////////////////////////
    int v1;                   ///< I describe v1
    int longervariablename;   ///< And I, describe v2
```


## ".cpp" files :
- Use double slashes.


# Part 2 - Style Guidelines :
- Place a ";" at the end of non-defined function declarations in header files.
- Don't indent "public", "protected" or private", same for the code it applies to.
- Place Member data of a class **after** the Methods.


## Full Exemple :
```c++
////////////////////////////////////////////////////////////
/// \brief yo
///
/// I go into more \a details lol.
////////////////////////////////////////////////////////////
class A
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief a function
    ///
    /// It's \a abstract too !
    ////////////////////////////////////////////////////////////
    virtual void foo() const = 0;

private:
    ////////////////////////////////////////////////////////////
    /// Member Data
    ////////////////////////////////////////////////////////////
    int v1;         ///< I describe v1
};


////////////////////////////////////////////////////////////
/// \brief I describe class B
////////////////////////////////////////////////////////////
class B : public A
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief a function
    ///
    /// This functions does :
    /// \li this
    /// \li and this !
    ////////////////////////////////////////////////////////////
    void foo() const override
    {
        int x = 5;
    }
};
```