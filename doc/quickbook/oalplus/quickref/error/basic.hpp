/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oalplus_error_Error_1

class Error : public std::runtime_error {
public:
    static const char* Message(ALenum error_code); /*<
    Returns a message for the specified [^error_code].
    >*/

    Error(const char* message); /*<
    Constructs a new instance of [^Error] with the specified
    error [^message].
    >*/
    ~Error() throw() {
    }

    ALenum Code() const; /*<
    Return the AL error code associated with this error.
    >*/

    const char* SourceFile() const; /*<
    Returns the name of the OALplus source file where the error occured.
    The result of this function is also influenced by the
    __OALPLUS_ERROR_NO_FILE preprocessor configuration option.
    If set to zero, this function behaves as described above, otherwise it
    returns a nullptr.
    >*/
    const char* SourceFunc() const; /*<
    Returns the name of the OALplus function where the error occured.
    The result of this function is also influenced by the
    __OALPLUS_ERROR_NO_FUNC preprocessor configuration option.
    If set to zero, this function behaves as described above, otherwise it
    returns a nullptr.
    >*/
    unsigned SourceLine() const;    /*<
       Returns the line of the OALplus source file where the error occured.
       The result of this function is also influenced by the
       __OALPLUS_ERROR_NO_LINE preprocessor configuration option.
       If set to zero, this function behaves as described above, otherwise it
       returns zero.
       >*/

    const char* ALLib() const;  /*<
     This function returns the name of the AL library ([^"al"], [^"alc"],
     [^"alut"]) where the error occured.
     The result of this function is also influenced by the
     __OALPLUS_ERROR_NO_AL_LIB preprocessor configuration option.
     If set to zero, this function behaves as described above, otherwise it
     returns nullptr.
     >*/
    const char* ALFunc() const; /*<
    This function returns the name of the failed OpenAL function
    (without the [^al] prefix) which is related to the error.
    The result of this function is also influenced by the
    __OALPLUS_ERROR_NO_AL_FUNC preprocessor configuration option.
    If set to zero, this function behaves as described above, otherwise it
    returns nullptr.
    >*/

    ALenum EnumParam() const;          /*<
             Returns the value of the enumeration parameter related to the error.
             If no enum parameter is available, this function returns zero.
             The result of this function is also influenced by the
             __OALPLUS_ERROR_NO_AL_SYMBOL preprocessor configuration option.
             If set to zero, this function behaves as described above, otherwise it
             returns zero.
             >*/
    const char* EnumParamName() const; /*<
    Returns the name of the enumeration parameter related to the error.
    If the enum parameter name is not available, this function returns
    zero.
    The result of this function is also influenced by the
    __OALPLUS_ERROR_NO_AL_SYMBOL preprocessor configuration option.
    If set to zero, this function behaves as described above, otherwise it
    returns nullptr.
    >*/

    virtual ALenum ObjectType() const;             /*<
                If the error is related to a AL object, then an object
                type enumeration value is returned. Otherwise the result is zero.
                >*/
    virtual ALint ObjectName() const;              /*<
                 If the error is related to a AL object, then the numeric
                 AL name of the object is returned. Otherwise the result
                 is a negative integer.
                 >*/
    virtual const std::string& ObjectDesc() const; /*<
    If the error is related to a AL object, then a std::string
    storing object description is returned. Otherwise the result
    is an empty std::string.
    >*/
};

//]
