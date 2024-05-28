function permute(str, l, r, fn){
    if (l == r) fn(str);
    else{
        for (let i = l; i <= r; i++){
            swap(str, l, i);
            permute(str, l + 1, r, fn);
            swap(str, l, i);
        }
    }
}
function swap(a, i, j){
    let temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}
let str = "ABC";
permute(str.split(''), 0, str.length-1, console.log);