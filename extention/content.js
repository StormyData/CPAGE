if(typeof browser==="undefined"){
	browser=chrome;
}
function naZewnatrz(img){
	var canvas = document.createElement("canvas");
    canvas.width = img.width;
    canvas.height = img.height;
    var ctx=canvas.getContext("2d");
	ctx.drawImage(img, 0, 0);
	var imgData = ctx.getImageData(0, 0, canvas.width, canvas.height);
	data = Array();
	for(var j=0;j<canvas.height;j+=1){
		data.push(Array());
		
		for(var i = 0; i < canvas.width; i+=1)
		{
			data[j].push(imgData.data[i*4+3+j*4*canvas.width]&1);
			
		}
	}
	var q=Array();
	var outp="";
	for(var i=0;i<canvas.width;i+=1){
		for(var j=0;j<canvas.height;j+=1){
			if(data[j][i]){
				tmpa = Array();
				for(var y=0;y<canvas.height;y+=1){
					tmpa.push(Array());
					for(var x = 0; x < canvas.width; x+=1)
						tmpa[y].push(0);
				}
				q.push([j,i]);
				var hh=0;
				var Mi=q[0][0];
				var mi=q[0][0];
				var Mj=q[0][1];
				var mj=q[0][1];
				while(q.length>hh){
					tmp=q[hh];
					hh+=1;
					if(tmp[0]<mi)
						mi=tmp[0];
					if(tmp[0]>Mi)
						Mi=tmp[0];
					if(tmp[1]<mj)
						mj=tmp[1];
					if(tmp[1]>Mj)
						Mj=tmp[1];
					if(tmp[0]-1>=0&&data[tmp[0]-1][tmp[1]]){
						q.push([tmp[0]-1,tmp[1]]);
						data[tmp[0]-1][tmp[1]]=0;
					}
					if(tmp[1]-1>=0&&data[tmp[0]][tmp[1]-1]){
						q.push([tmp[0],tmp[1]-1]);
						data[tmp[0]][tmp[1]-1]=0;
					}
					if(tmp[0]+1<canvas.height&&data[tmp[0]+1][tmp[1]]){
						q.push([tmp[0]+1,tmp[1]]);
						data[tmp[0]+1][tmp[1]]=0;
					}
					if(tmp[1]+1<canvas.width&&data[tmp[0]][tmp[1]+1]){
						q.push([tmp[0],tmp[1]+1]);
						data[tmp[0]][tmp[1]+1]=0;
					}	
				}
				for(hh=0;hh<q.length;hh+=1){
					tmpa[q[hh][0]-mi][q[hh][1]-mj]=1;
				}
				Mi-=mi-1;
				Mj-=mj-1;
				binary=Array();
				for(var x=0;x<Mi;x+=1){
					for(var y=0;y<Mj;y+=1){
						binary.push(tmpa[x][y]);
					}
				}
				bytes=Array();
				bytes.push(Mj);
				bytes.push(Mi);
				var tmpz=0;
				for(var x=0;x<binary.length;x+=1){
					tmpz=tmpz*2+binary[x];
					if( x%8==7){
						bytes.push(tmpz);
						tmpz=0;
					}
				}
				bytes.push(tmpz);
				bytesa = String();
				for(var x=0;x<bytes.length;x+=1){
					bytesa+=String.fromCharCode(bytes[x]);
				}
				var out="";
				bytesa=btoa(bytesa);
				for(var x=0;x<10;x+=1){
					tav=digits.digits[String(x)];
					for(var y=0;y<tav.length;y+=1){
						if(bytesa==tav[y]){
							out=String(x);
							break;
						}
					}
					if(out!=""){
						break;
					}
				}
				outp+=out;
				q=Array();
			}
		}
	}
	console.log(outp);
	document.body.firstChild.nextSibling[7].value=outp;
}
browser.runtime.onMessage.addListener(
  function(request, sender, sendResponse) {
	digits = JSON.parse(request.greeting);
	setTimeout(function(){naZewnatrz(document.getElementById("imgCaptcha"));},10);
  }
);
  
  