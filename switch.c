switch (comandos=0)
{
case 'CT':
    operador_ct();
break;
case 'RT':
    operador_rt();
break;
case 'AT':
    operador_at();
break;
case 'LT':
    operador_lt();
break;
case 'IR':
    operador_ir();
break;
case 'BR':
    if(comandos[2] == N)
    operador_brN();
    if(comandos[2] == U)
    operador_brU();
break;
case 'AR':
    operador_ar();
break;
case 'RR':
    operador_rr();
break;
case 'CI':
    if(comandos[2] == A)
    operador_ciA();
    if(comandos[2] == H)
    operador_ciH();
break;
case 'RI':
    operador_ri();
break;
case 'GI':
    operador_gi();
break;

}