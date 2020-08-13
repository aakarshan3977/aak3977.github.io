/* Add any JavaScript you need to this file. */

var slideIndex = 0;

function change() {
  var i;
  var x = document.getElementsByClassName('show');
  if (x.length === 0) return;
  for (i = 0; i < x.length; i++) {
    x[i].style.display = 'none';
  }
  slideIndex++;
  if (slideIndex > x.length) {
    slideIndex = 1;
  }
  x[slideIndex - 1].style.display = 'block';
  setTimeout(change, 2000);
}
window.addEventListener('load', function() {
  change();
});
window.addEventListener('load', () => {
  const order = document.getElementById('orderNum');

  const inquiryRadioElements = document.querySelectorAll('input[name="button"]');
  inquiryRadioElements.forEach(element => {
    element.addEventListener('change', () => {
      if (element.value === 'Order Problem') {
        order.style.display = 'block';
      } else {
        order.style.display = 'none';
      }
    });
  });
});
