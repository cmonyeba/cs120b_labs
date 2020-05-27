
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

/* complete the state machine. */

void Detect_Max_Amp()
{
    switch(detect_max_amp_state)
    {
        case DMAInit:
		detect_max_amp_state=DMAInit;
            break;
        
        default:
            break;
    }
    switch(detect_max_amp_state)
    {
        case DMAInit:amp=PINA&0xF8;
            break;
        default:
            break;
    }
}
