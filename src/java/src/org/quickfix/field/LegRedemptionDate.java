package org.quickfix.field; 
import org.quickfix.UtcDateField; 
import java.util.Date; 

public class LegRedemptionDate extends UtcDateField 
{ 

  public LegRedemptionDate() 
  { 
    super(254);
  } 
  public LegRedemptionDate(Date data) 
  { 
    super(254, data);
  } 
} 