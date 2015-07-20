#ifndef EXCEPTIONS_H
#define	EXCEPTIONS_H

class LoadModelFileException: public std::exception
{
  public:
  virtual const char* what() const throw()
  {
        return "Error loading classifier from file. Check if 'models' folder is in the program running directory.";
  }
};

#endif	/* EXCEPTIONS_H */
