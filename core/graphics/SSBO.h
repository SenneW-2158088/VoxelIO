#pragma once

/* Here lies the most beautiful piece of software, the magical infinite buffer */
template<class T>
class SSBO {
private:
  unsigned int id; // used for binding to the correct index
  unsigned int SBO;
public:
  void setId(unsigned int id) { this->id = id; };
public:
  unsigned int getId() const { return id; };
  unsigned int getSBO() const {return SBO; };
protected:
  // Update the buffer with the supplied array
  void updateBuffer(T data[], unsigned int size);
public:
  SSBO();
  ~SSBO();

  void bind() const;
};
