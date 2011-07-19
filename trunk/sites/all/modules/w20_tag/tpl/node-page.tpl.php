<?php 
global $base_url, $base_path;

if ($node->field_page_layout[0]['value'] != '') {
	include('/home/w20/public_html/sites/all/w20/php/tag/function.php');
	switch ($node->field_page_layout[0]['value']) {
		default:
		include('/home/w20/public_html/sites/all/w20/php/tpl/node-page-' . $node->field_page_layout[0]['value'] . '.tpl.php');
		break;
		
	}
} else {

?>

	<div id="pagina">
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

	<div class="field field-type-text field-field-layout">
	  <!-- <h3 class="field-label">Layout</h3> -->
	  <div class="field-items">
		  <div class="field-item"><?php print $node->field_page_layout[0]['value'] ?></div>
	  </div>
	</div>

	<div class="field field-type-text field-field-body">
	  <!-- <h3 class="field-label">Corpo</h3> -->
	  <div class="field-items">
		  <div class="field-item"><?php print $node->content['body']['#value'] ?></div>
	  </div>
	</div>

	<div class="field field-type-filefield field-field-imagem">
	  <!-- <h3 class="field-label">Imagem</h3> -->
	  <div class="field-items">
		<?php foreach ((array)$node->field_page_imagem as $item) { ?>
		  <div class="field-item"><img src="<?php print $base_url . '/' . $item['filepath'] ?>" /></div>
		<?php } ?>
	  </div>
	</div>



	  </div>

	  <div class="clear-block">
		<div class="meta">
		<?php if ($taxonomy): ?>
		  <div class="terms"><?php print $terms ?></div>
		<?php endif;?>
		</div>

		<?php if ($links): ?>
		  <div class="links"><?php print $links; ?></div>
		<?php endif; ?>
	  </div>

	</div>
	</div>

<?php 
} // final do else 

?>