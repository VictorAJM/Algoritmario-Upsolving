void findLongestPalindromicString(string text) 
{ 
  int N = text.length(); 
  if (N == 0) 
    return; 

  N = 2 * N + 1; 

  int L[N]; 
  L[0] = 0; 
  L[1] = 1; 

  int C = 1; 
  int R = 2; 
  int i = 0; 
  int iMirror; 
  int expand = -1; 
  int diff = -1; 
  int maxLPSLength = 0; 
  int maxLPSCenterPosition = 0; 
  int start = -1; 
  int end = -1; 
    int r = -1;
  for (i = 2; i < N; i++) { 
    iMirror = 2 * C - i; 
    expand = 0; 
    diff = R - i; 
    if (diff >= 0) { 
      if (L[iMirror] < diff) 
        L[i] = L[iMirror]; 
      else if (L[iMirror] == diff && R==N-1) 
        L[i] = L[iMirror]; 
      else if (L[iMirror] == diff && R<N-1) { 
        L[i] = L[iMirror]; 
        expand = 1; 
      } 
      else if (L[iMirror] > diff) { 
        L[i] = diff; 
        expand = 1; 
      } 
    } 
    else { 
      L[i] = 0; 
      expand = 1; 
    } 

    if (expand == 1) { 
      while (((i+L[i]) < N && (i-L[i]) > 0) 
        && (((i + L[i] + 1) % 2 == 0) 
          || (text[(i + L[i] + 1) / 2] 
            == text[(i - L[i] - 1) / 2]))) { 
        L[i]++; 
      } 
    } 
    if (L[i] >= maxLPSLength) { 
            if(L[i]==maxLPSLength){
                r++;
            }else{
                r=1;
                maxLPSLength = L[i]; 
                maxLPSCenterPosition = i; 
            }
    } 
    if (i + L[i] > R) { 
      C = i; 
      R = i + L[i]; 
    } 
  } 
    cout<<maxLPSLength<<"\n";

//start=(maxLPSCenterPosition-maxLPSLength)/2; 
//end=start + maxLPSLength - 1; 
} 