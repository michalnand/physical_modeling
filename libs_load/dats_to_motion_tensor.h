#ifndef _DATS_TO_MOTION_TENSOR_H_
#define _DATS_TO_MOTION_TENSOR_H_

#include <string>
#include "motion_tensor.h"


class DatsToMotionTensor
{
  public:

    DatsToMotionTensor();
    DatsToMotionTensor(
                        std::string dats_json_file_name,
                        std::string motion_tensor_file_name
                      );

    DatsToMotionTensor(
                        std::string dats_json_file_name,
                        std::string motion_tensor_file_name,
                        MotionTensor &other
                      );

    DatsToMotionTensor(DatsToMotionTensor& other);
    DatsToMotionTensor(const DatsToMotionTensor& other);

    DatsToMotionTensor& operator= (DatsToMotionTensor& other);
    DatsToMotionTensor& operator= (const DatsToMotionTensor& other);

    virtual ~DatsToMotionTensor();

    void load( std::string dats_json_file_name,
               std::string motion_tensor_file_name);

    void load(  std::string dats_json_file_name,
                std::string motion_tensor_file_name,
                MotionTensor &other);

  protected:
    void copy(DatsToMotionTensor& other);
    void copy(const DatsToMotionTensor& other);

  public:
    MotionTensor& tensor()
    {
      return motion_tensor;
    }


  private:
    MotionTensor motion_tensor;
};

#endif
