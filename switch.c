switch (comandos=0)
{
case 'CT':
      operacao_ct();
break;
case 'RT':
      operacao_rt();
break;
case 'AT':
      operacao_at();
break;
case 'LT':
      operacao_lt();
break;
case 'IR':
      operacao_ir();
break;
case 'BR':
    if(comandos [1] == N)
      operacao_brN();
      if(comandos [1] == U)
      operacao_brU();
break;
case 'AR':
      operacao_ar();
break;
case 'RR':
      operacao_rr();
break;
case 'CI':
    if(comandos [1] == A)
      operacao_ciA();
      if(comandos [1] == H)
      operacao_ciH();
break;
case 'RI':
      operacao_ri();
break;
case 'GI':
      operacao_gi();
break;
}