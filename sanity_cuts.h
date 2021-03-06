#ifndef SANITY_CUTS_H
#define SANITY_CUTS_H



//Please put TMath Before this


//Takes in data and spits out a delta t
/*
 p = particle momentum p[k]
 p0 = p[0]
 d = sc_r[scindex]
 d0 = sc_r[sc[0]-1]
 t = sc_t[scindex]
 t0 = sc_t[sc[0]-1]
 m = mass you're looking for 
 */

bool sanity_electron( UChar_t dc, UChar_t cc, UChar_t ec, UChar_t sc, Char_t stat, Char_t dc_stat, Char_t q )
{
	bool sane_elec = kFALSE;
	if((int)dc>0)
	{
		if((int)cc>0)
		{
			if((int)ec>0)
			{
				if((int)sc>0)
				{
					if((int)stat>0)
					{
						if((int)dc_stat>0)
						{
							if((int)q==-1)
							{
								sane_elec = kTRUE;
							}
						}
					}
				}
			}
		}
	}
	return sane_elec;
}


//Note that q is set to +1. This is because I'll only be looking for protons and positive pions
//Getting rid of charge due to multiple topography. Putting the charge into hid.h
bool sanity_hadron( UChar_t dc, UChar_t sc, Char_t stat, Char_t dc_stat)
{
	bool sane_elec = kFALSE;
	if((int)dc>0)
	{
		if((int)sc>0)
		{
			if((int)stat>0)
			{
				if((int)dc_stat>0)
				{
					sane_elec = kTRUE;
				}
			}
		}				
	}
	return sane_elec;
}


#endif /* SANITY_CUTS_H */