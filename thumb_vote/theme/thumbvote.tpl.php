<div class="thumb-vote" data-nid="<?php echo $nid;?>">
  <span class="error-msg"></span>
  <span class="votes <?php echo
  $votes != 0 
    ? ($votes < 0 ? 'negative' : 'positive')
    : '';
  ?>"><?php echo $votes; 
  ?></span>
  
  <a class="up <?php if($user_vote > 0) echo 'active'; ?>"></a>
  <a class="down <?php if($user_vote < 0) echo 'active'; ?>"></a>
</div>