(function($){
  "use strict";
  
  $(function(){
    /**
     * Send vote to JSON interface, alert error or update vote count.
     * returns nothing.
     * @param {Number} vote         New vote state
     * @param {Object} $voteWrapper Wrapping element as jQuery object
     * @returns {undefined}
     */
    function doVote(vote,$voteWrapper){
      var $voteSumLbl = $voteWrapper.find('.votes');
      var id = $voteWrapper.attr('data-id');
      var type = $voteWrapper.attr('data-enttype');
      
      //POST vote to the JSON interface, see thumb_vote.module
      $.post(
        Drupal.settings.basePath + '?q=json/thumbvote',
        {
          vote :vote,
          id   : id,
          type : type
        },

      // Callback for the vote request. Handles error message, 
      // highlight of active selection as well as showing the new vote sum
      function(response){
        if(response.success){
          //Success! Lets update the vote count!
          $voteSumLbl.text(response.votes);
          
          //style vote score if its not 0
          $voteSumLbl.removeClass('negative');
          $voteSumLbl.removeClass('positive');
          
          if(response.votes !== 0){
            $voteSumLbl.addClass(
              response.votes > 0 
              ? 'positive' 
              : 'negative'
            );  
          }
          
          //Highlight the current selection with the css class 'active'.
          $voteWrapper.find('.up,.down').removeClass('active');
          if(response.userVote !== 0){
            $voteWrapper.find(response.userVote > 0 ? '.up':'.down').addClass('active');
          }
          
        } else {
          
          //If something fails, then prompt the user with an error message.
          $('.error-msg').hide();
          
          var $errorWrapper = $voteWrapper.find('.error-msg');
          $errorWrapper.text(response.error);
          $errorWrapper.fadeIn();
        }
      });
    }
    
    //Register event handlers for up/down voting.
    $('.thumb-vote .up,.down').live('click',function(){
      var $this = $(this);
      
      //If clicking on an active selection, then reset the rating (0).
      //If clicking on an inactive selection then evaluate if its up (1) or down (-1)
      var vote = $this.hasClass('active') 
        ? 0
        : ($this.hasClass('up') ? 1 : -1);
      
      doVote(vote, $this.parent());
    });
  });
  
})(jQuery);