package org.quickfix.field; 
import org.quickfix.StringField; 
import java.util.Date; 

public class Scope extends StringField 
{ 
public static final char LOCAL = '1'; 
public static final char NATIONAL = '2'; 
public static final char GLOBAL = '3'; 

  public Scope() 
  { 
    super(546);
  } 
  public Scope(String data) 
  { 
    super(546, data);
  } 
} 