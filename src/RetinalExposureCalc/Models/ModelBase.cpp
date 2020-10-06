#include "ModelBase.hpp"


namespace RetinalExposureCalc
{

  void ModelBase::addReference(std::string ref)
  {
    m_References.push_back(ref);
  }

  void ModelBase::addNote(std::string note)
  {
    m_Notes.push_back(note);
  }

  void ModelBase::addToDescription(std::string desc)
  {
    m_Description += desc;
  }

  std::vector<std::string> ModelBase::getReferences() const
  {
    return m_References;
  }

  std::vector<std::string> ModelBase::getNotes() const
  {
    return m_Notes;
  }

  std::string ModelBase::getDescription() const
  {
    return m_Description;
  }


}
