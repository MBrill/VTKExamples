#ifndef COMPUTE_H
#define COMPUTE_H


//! Compute the sum of two long numbers
/*!
 * Here is place for a longer description
 */
class Compute 
{
//
// public
//
public:
    //! default constructor
    /*!
     * values:
     *     a=1,
     *     b=1.
     */
    Compute(void);
    //! copy constructor
    Compute(Compute &copy);
    //! constructor with two numbers
    /*!
     * @param first   first number
     * @param second  second number
     */
    Compute(long first, long second);
    //! do the actual computation
    /*!
     * @return the sum
     */
    long compute();
    //! set the first number
    void setA(long);
    //! set the second number
    void setB(long);
    //! get the first number
    long getA() const;
    //! get the second number
    long getB() const;

//
// private
//
protected:
    //! first number
    long a;
    //! second number
    long b;
};

// ------------------- Inline Section -----------------------------
inline long Compute::getA() const { return a;}

inline long Compute::getB() const  { return b;}
#endif /* COMPUTE_H */
