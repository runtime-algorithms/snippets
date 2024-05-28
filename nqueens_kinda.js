function finalTry5(N,{row,col}){
  let nrm=new Uint16Array(N+N-1), rev=new Uint16Array(N+N-1), ver=new Uint16Array(N);
  //let random=array=>Math.floor(Math.random()*array.length);
  //let random=array=>crypto.getRandomValues(new Uint32Array(1))[0]%array.length;
  //nrm for backslash diagonal, rev for frontslash diagonal, ver for vertical
  function draw(arr,L){
    let str="", N=arr.length, lim=L||N;
    for(let i=0;i<N;i++){
      for(let j=0;j<N;j++) str+=arr[i]===j&&i<lim?'Q':'.';
      str+='\n';
    }
    return str;
  }
  let arr=Array(N), c=col, allSpots=[[col]], i=1;
  arr[row]=col; nrm[col-row+N-1]=1; rev[col+row]=1; ver[col]=1;
  c=(c+1==N)?0:((c+2)%N);
  //manditory placed, now for the iterations
  while(i<N){
    let r=(i+row)%N, spots=[], backtracked=false;
    for(let k=0;k<N;k++){
      if(!nrm[c-r+N-1] && !rev[c+r] && !ver[c])
        spots.push(c);
      c=(c+1)%N;
    }
    //c as spot with lowest NRM+REV+VER count
    while(!spots.length){
      //console.log(draw(arr,i),1)
      if(i===1) return ""; //backtracked all the way to manditory and no more options
      r=(--i+row)%N;
      spots=allSpots.pop();
      c=arr[r]; nrm[c-r+N-1]=0; rev[c+r]=0; ver[c]=0; //delete old spot
      if(!spots.length) continue;
      backtracked=true;
      allSpots.push(spots);
      c=spots.splice(Math.floor(Math.random()*spots.length),1)[0]; //select new spot
      arr[r]=c; nrm[c-r+N-1]=1; rev[c+r]=1; ver[c]=1; //set new spot
      c=(c+1==N)?0:((c+2)%N); i++; break; //addition
      //console.log(draw(arr,i),JSON.stringify(spots),2)
    }
    if(backtracked) continue;
    allSpots.push(spots);
    c=spots.splice(Math.floor(Math.random()*spots.length),1)[0]; //select new spot
    arr[r]=c; nrm[c-r+N-1]=1; rev[c+r]=1; ver[c]=1; //set new spot
    c=(c+1==N)?0:((c+2)%N); i++; //addition
    //console.log(draw(arr,i),3)
  }
  return draw(arr);
}
console.log(finalTry5(8,{row:0,col:1}))
//console.log(finalTry5(326,{row:261,col:38})) //hangs