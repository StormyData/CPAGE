if(typeof browser==="undefined"){
	browser=chrome;
}
function getDatabase(x){
	browser.tabs.query({active: true, currentWindow: true},function(tabs){
		if(typeof x.idziennik_base === "undefined"){
			if(browser!=chrome)
				console.log("downloading database...");
			var xhr = new XMLHttpRequest();
			xhr.open("GET", "https://raw.githubusercontent.com/AmbitiousST/CPAGE/master/data.json", false);
			xhr.send();
			browser.tabs.sendMessage(tabs[0].id, {greeting: xhr.response}, function(response){});
			let idziennik_base = {};
			idziennik_base["idziennik_base"] = xhr.response;
			browser.storage.local.set(idziennik_base);
		}else{
			browser.tabs.sendMessage(tabs[0].id, {greeting: x.idziennik_base}, function(response){});
		}
	});
}
browser.webRequest.onHeadersReceived.addListener(
	function(e){
		if(browser==chrome){
				browser.storage.local.get(["idziennik_base"],getDatabase);
		}else{
				browser.storage.local.get("idziennik_base").then(getDatabase);
		}
		
	},
	{urls: ["https://iuczniowie.progman.pl/idziennik/ws_czynnosciadm.asmx/GetCaptacha"]},
	["blocking", "responseHeaders"]
);
