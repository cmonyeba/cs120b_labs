//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/

void Detect_EQ()
{
    unsigned char i = 0;
    switch(detect_eq_state)
    {
        case DEQInit:
            detect_eq_state=DEQWait;
            break;
	case DEQWait:
	    if(amp>0){
		    detect_eq_state=DEQFound;
	    }else{
		    detect_eq_state=DEQWait;
	    }break;
	case DEQFound:
	    detect_eq_state=DEQFall;
	    break;
	case DEQFall:
	    if(amp<=0&&i>=10){
		    i=0;
		    detect_eq_state=DEQWait;
	    }else{
		    detect_eq_state=DEQFall;
	    }break;
        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
            break;
	case DEQWait:
	    break;
	case DEQFound:
	    quake=~quake&0x02;
	    break;
	case DEQFall:
	    if(amp<=0){
	    	i++;
	    }else{
		i=0;
	    }
	    break;
        default:
            break;
    }
}
