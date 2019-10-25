"{\
	'general':\
	{\
		'name':'Hydro',\
		'instance':1,\
		'interval':500\
	},\
	'components':[\
		{\
			'name':'Analog',\
			'params':[\
/* samples */	8,\
/* resolution*/	12,\
				false,\
/* pH probe */	true,\
/*tur. probe*/	true,\
				false,\
				false,\
				false,\
				0,\
/* pH */		3,\
/* turbidity*/	0,\
				0,\
				0,\
				0\
			]\
		},\
		{\
			'name':'MS5803',\
			'params':[119,255]\
		},\
		{\
			'name':'WiFi',\
			'params':[\
/*needed*/		'',\
				''\
			]\
		},\
		  {\
      'name':'SD',\
      'params': 'default'\
    },\
    {\
      'name':'DS3231',\
      'params':'default'\
    },\
		{\
			'name':'TempSync',\
/*ms5803,analog*/'params':[2110,2001]\
		},\
    {\
      'name':'Loom_Sleep_Manager',\
      'params':[true,false,3]\
    },\
    {\
      'name':'Loom_Interrupt_Manager',\
      'params':[12]\
    }\
	]\
}"
