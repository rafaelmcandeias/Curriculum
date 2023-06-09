package woo.core.enumeration;

public enum Statute{
  NORMAL("NORMAL"), SELECTION("SELECTION"), ELITE("ELITE");

  private String _statute;

  /**
  * @param statute client statute 
  */
  private Statute(String statute){
    _statute = statute;
  }

  @Override
  public String toString(){
    return _statute;
  }

}
