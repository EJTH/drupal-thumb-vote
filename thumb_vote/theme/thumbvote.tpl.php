<div class="thumb-vote" data-id="<?php echo $entid; ?>" data-enttype="<?php echo $type; ?>">
  <span class="error-msg"></span>
  <span class="votes"><?php echo $votes; ?></span>
  
  <a class="up <?php if($user_vote > 0) echo 'active'; ?>"></a>
  <a class="down <?php if($user_vote < 0) echo 'active'; ?>"></a>
</div>