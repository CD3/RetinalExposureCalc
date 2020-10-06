#pragma once

/** @file ModelBase.hpp
  * @brief 
  * @author C.D. Clark III
  * @date 09/17/20
  */

#include <string>
#include <vector>


namespace RetinalExposureCalc
{

class ModelBase
{
  protected:
    std::vector<std::string> m_References;
    std::vector<std::string> m_Notes;
    std::string m_Description;

  public:

  void addReference(std::string ref);
  void addNote(std::string ref);
  void addToDescription(std::string desc);

  std::vector<std::string> getReferences() const;
  std::vector<std::string> getNotes() const;
  std::string getDescription() const;


};

}
