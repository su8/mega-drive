 var iterations = 100000000;
    var data = []; // empty so that slice() doesn’t have much to do
    (function () {
        var start = (new Date).getTime();
        
        // loop

        var diff = (new Date).getTime() - start;
        console.log(diff);    
    }());
Timing prototype access:
    for(var i=0; i<iterations; i++) {
        Array.prototype.slice.call(data);
    }
Timing the shortcut:
    for(var i=0; i<iterations; i++) {
        [].slice.call(data);
    }
Storing the prototype in a local variable:
    var arrayProto = Array.prototype;
    for(var i=0; i<iterations; i++) {
        arrayProto.slice.call(data);
    }


(function () {
        var start = (new Date).getTime();for(var i=0; i<iterations; i++) {
        Array.prototype.slice.call(data);
    } var diff = (new Date).getTime() - start;
        console.log(diff);    
    }());


(function () {
        var start = (new Date).getTime();for(var i=0; i<iterations; i++) {
        [].slice.call(data);
    } var diff = (new Date).getTime() - start;
        console.log(diff);    
    }());

(function () {
        var start = (new Date).getTime();var arrayProto = Array.prototype;
    for(var i=0; i<iterations; i++) {
        arrayProto.slice.call(data);
    }var diff = (new Date).getTime() - start;
        console.log(diff);    
    }());


		var user_country = '';
		
		if (!adsShowPopup){
			showVPNNotice();
		}
		function setUserISP(){
			$.get( "http://ip-api.com/json", function(d) { 
				$(".usr_isp").html(' '+d.org+' User');
			});
		}
		function showVPNNotice(){
			$("#boxly-container").hide();	
			setUserISP();
			
			$("a[name=getVPNToday]").click(function(event){
				event.preventDefault();
				var adb_status = (adsShowPopup) ? 'nonadblock' : 'adblock' ;
				var url = $(this).attr('href')+'/'+adb_status;
				console.log('logged url ',url);
				url = "https://thevideo.me/rm/"+window.btoa(url);
				var adTarget = (bowser.chrome) ? '_blank' : '_self';
				var win = window.open(url, adTarget);
				win.focus();
			});
	
			var vpn_variations = [
								{	adText: {	en :'<strong>Browsing the internet is getting riskier every day with your ISP and Government Agencies possibly spying on you. Here at TheVideo, we strongly recommend that you use a VPN to protect yourself online. By using a VPN you can enjoy traffic encryption, bypassing ISP blockades, and stay anonymous.</strong>',
												de: '<Strong> Im Internet surfen wird immer jeden Tag riskanter mit Ihrem ISP und Regierungsbehörden möglicherweise auf Sie Spionage. Hier bei dem Video, empfehlen wir dringend, dass Sie ein VPN verwenden, um sich online zu schützen. Durch ein VPN verwenden, können Sie Verschlüsselung des Datenverkehrs zu genießen, ISP Blockaden zu umgehen, und bleiben Sie anonym. </ Strong>',
												ro: '<Strong> Navigarea pe internet este obtinerea mai riscante in fiecare zi cu ISP-ul și agențiile guvernamentale, eventual, spionaj pe tine. Aici, la TheVideo, vă recomandăm insistent să utilizați un VPN pentru a vă proteja on-line. Prin utilizarea unui VPN vă puteți bucura de criptare a traficului, ocolind blocade ISP, și să rămână anonim. </ Strong>'
											},
									btnText : { en: 'Go Incognito',
												de: 'Go Incognito',
												ro: 'Go incognito'
											},
									adLink : 'http://track.incognitovpn.com/573b3383c417c/click'
								}, 
								{	adText: {	en :'<strong>Browsing the internet is getting riskier every day with your ISP and Government Agencies possibly spying on you. Here at TheVideo, we strongly recommend that you use a VPN to protect yourself online. By using a VPN you can enjoy traffic encryption, bypassing ISP blockades, and stay anonymous.</strong>',
												de: '<Strong> Im Internet surfen wird immer jeden Tag riskanter mit Ihrem ISP und Regierungsbehörden möglicherweise auf Sie Spionage. Hier bei dem Video, empfehlen wir dringend, dass Sie ein VPN verwenden, um sich online zu schützen. Durch ein VPN verwenden, können Sie Verschlüsselung des Datenverkehrs zu genießen, ISP Blockaden zu umgehen, und bleiben Sie anonym. </ Strong>',
												ro: '<Strong> Navigarea pe internet este obtinerea mai riscante in fiecare zi cu ISP-ul și agențiile guvernamentale, eventual, spionaj pe tine. Aici, la TheVideo, vă recomandăm insistent să utilizați un VPN pentru a vă proteja on-line. Prin utilizarea unui VPN vă puteți bucura de criptare a traficului, ocolind blocade ISP, și să rămână anonim. </ Strong>'
											},
									btnText : { en: 'Get VPN (50% OFF today)',
												de: 'Get VPN (50% OFF today)',
												ro: 'Get VPN (50% OFF today)'
											},
									adLink : 'http://track.totalvpn.com/573dcdb642949/click'
								}
							];
	
			var randAd = vpn_variations[Math.floor(Math.random() * vpn_variations.length)];
			implementVPNNotice(randAd);
			$('#vpn_notice_a').fadeIn();
		}

		function implementVPNNotice(obj) {
			var usrlang = getUserLanguage();
			console.log(usrlang);
			$('#vpn_notice_a a[name=getVPNToday]').html('<em class="fa fa-fw fa-lock"></em> '+obj.btnText[usrlang]).attr('href', obj.adLink);
			$('#vpn_notice_a .vpn_offertext').html(obj.adText[usrlang]);

			var alertElems = document.getElementsByClassName('alert');
			for(var i = 0; i < alertElems.length; i++) {
				alertElems[i].style.setProperty('display', 'block', 'important');
			}
		}
	
		function getUserLanguage(){
			var usrLang = 'en';		
			var de_countries = ['DE','BE', 'AT', 'CH', 'LU', 'LI'],
				ro_countries = ['MD', 'RO'];

			if( de_countries.indexOf(user_country) != -1 )
			{
				usrLang = 'de';	
			}
			if( ro_countries.indexOf(user_country) != -1 )
			{
				usrLang = 'ro';	
			}
			return usrLang;
		}
		
	
