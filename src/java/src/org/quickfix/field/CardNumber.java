package org.quickfix.field; 
import org.quickfix.StringField; 
import java.util.Date; 

public class CardNumber extends StringField 
{ 

  public CardNumber() 
  { 
    super(489);
  } 
  public CardNumber(String data) 
  { 
    super(489, data);
  } 
} 