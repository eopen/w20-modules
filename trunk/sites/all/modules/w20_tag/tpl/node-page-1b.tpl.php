
<?php global $base_url; ?>

<div id="pagina" class="modelo-1b">
<?php
// $Id: node.tpl.php,v 1.5 2007/10/11 09:51:29 goba Exp $
?>
<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?>">

<?php print $picture ?>

<?php if ($page == 0): ?>
  <h2><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
<?php endif; ?>

  <?php if ($submitted): ?>
    <span class="submitted"><?php print $submitted; ?></span>
  <?php endif; ?>

  <div class="content clear-block">

<div class="field field-type-filefield field-field-imagem" style="boder: solid 1px #f00 !important;">
  <!-- não é necessãrio exibir este label  <h3 class="field-label">Imagem</h3> -->
  <div class="field-items">
      <div class="field-item">
	  
	  <?php print '<a rel="lightbox" href="/' . $node->field_page_imagem[0]['filepath'] . '" >' . theme('imagecache', '240x160', $node->field_page_imagem[0]['filepath'], '', '',  array('id'=>'small_image_id','class'=>'image')) . '</a>'; ?>
	  
	  </div>
  </div>
</div>

<div class="field field-type-text field-field-body">
  <!-- não é necessãrio exibir este label  <h3 class="field-label">Corpo</h3> -->
  <div class="field-items">
      <div class="field-item"><?php print $node->content['body']['#value'] ?></div>
  </div>
</div>

  </div>



</div>
</div>
