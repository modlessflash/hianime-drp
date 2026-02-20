function waitForElm(selector) { // https://stackoverflow.com/questions/5525071/how-to-wait-until-an-element-exists
    return new Promise(resolve => {
        if (document.querySelector(selector)) {
            return resolve(document.querySelector(selector));
        }

        const observer = new MutationObserver(mutations => {
            if (document.querySelector(selector)) {
                observer.disconnect();
                resolve(document.querySelector(selector));
            }
        });

        observer.observe(document.body, {
            childList: true,
            subtree: true
        });
    });
}

function once() {
  const title   = document.getElementsByClassName("text-white dynamic-name")[0].text;
  const episode = document.getElementsByClassName("server-notice")[0].children[0].children[0].textContent;
  const info    = `${title} :: ${episode}`
  fetch(`http://localhost:9293/hianimedrp?info=${encodeURIComponent(info)}`);
}

function start() {
  once();
  setInterval(function() {
    once();
  }, 30000);
}

waitForElm(".server-notice").then((elm) => {
  start();
});